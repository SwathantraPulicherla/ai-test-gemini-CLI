#!/usr/bin/env python3
import google.generativeai as genai
import os
import glob
import argparse
from pathlib import Path
import re

def read_source_file(c_file, h_files):
    """Read a specific C source file and related headers"""
    source_code = ""
    
    # Read header files first
    for h_file in h_files:
        try:
            with open(h_file, 'r') as f:
                source_code += f"// Header: {h_file}\n{f.read()}\n\n"
        except Exception as e:
            print(f"Error reading {h_file}: {e}")
    
    # Read the C source file
    try:
        with open(c_file, 'r') as f:
            source_code += f"// Source: {c_file}\n{f.read()}\n\n"
    except Exception as e:
        print(f"Error reading {c_file}: {e}")
    
    return source_code

def extract_functions(source_code):
    """Extract function signatures from C code"""
    function_pattern = r'\w+\s+\w+\([^)]*\)\s*\{'
    functions = re.findall(function_pattern, source_code)
    return functions

def generate_test_prompt(source_code, issue_title, issue_body):
    """Create a detailed prompt for Gemini"""
    """Generate compilable, functional tests with strict constraints"""
    
    constraints = """
    IMPORTANT CONSTRAINTS - MUST FOLLOW STRICTLY:

    1. **NO FUNCTION REDEFINITION**: Only write test functions, never redefine existing functions
    2. **UNITY STANDARD ASSERTIONS ONLY**: 
    - ALLOWED: TEST_ASSERT_TRUE, TEST_ASSERT_FALSE, TEST_ASSERT_EQUAL, TEST_ASSERT_NULL, TEST_ASSERT_NOT_NULL, TEST_ASSERT_FLOAT_WITHIN
    - FORBIDDEN: TEST_ASSERT_NOT_NAN, TEST_ASSERT_NOT_INF, and other non-standard assertions
    3. **NO MOCKING FRAMEWORKS**: Do not use mock(), will_return(), or CMock functions
    4. **TEST ACTUAL IMPLEMENTATIONS**: Call the real functions, don't create test stubs
    5. **PROPER HEADERS**: Include "unity.h" and the source file headers
    6. **CORRECT SIGNATURES**: Test functions must be void test_name(void)

    COMMON MISTAKES TO AVOID:
    - Redefining existing functions (causes linker errors)
    - Using non-existent Unity macros (causes compilation errors)  
    - Including mocking code without CMock (causes linker errors)
    - Missing necessary header includes

    OUTPUT REQUIREMENTS:
    - Must be compilable with gcc and Unity framework
    - Must follow standard Unity test structure
    - Must use only the assertions listed above
    """
    functions = extract_functions(source_code)
    
    prompt = f"""
    {constraints}
TASK: Generate comprehensive unit tests for C code using the Unity testing framework.

SOURCE CODE:
{source_code}

FUNCTIONS DETECTED:
{chr(10).join(functions) if functions else 'No functions detected'}

ISSUE TITLE: {issue_title}
ISSUE DESCRIPTION: {issue_body}

REQUIREMENTS:
1. Generate clean, compilable Unity tests that follow all constraints above.
Output only the C code without any explanations or markdown formatting.
2. Include both normal operation and edge cases
3. Test error conditions and boundary values
4. Include proper setup/teardown functions
5. Use descriptive test function names
6. Include necessary headers and mocks

OUTPUT FORMAT:
- Complete C file with Unity tests
- Include #include directives for necessary headers
- Use TEST_ASSERT_* macros appropriately
- Group related tests in test suites

Generate the complete test file:
```c
"""
    return prompt

def main():
    api_key = os.environ.get('GEMINI_API_KEY')
    if not api_key:
        print("Error: GEMINI_API_KEY environment variable not set")
        exit(1)
    
    issue_title = os.environ.get('ISSUE_TITLE', 'Generate unit tests')
    issue_body = os.environ.get('ISSUE_BODY', '')
    
    # Configure Gemini
    genai.configure(api_key=api_key)
    model = genai.GenerativeModel('gemini-1.5-flash')
    
    # Find all C files
    c_files = glob.glob("*.c")
    h_files = glob.glob("*.h")
    
    if not c_files:
        print("No C source files found to analyze")
        exit(1)
    
    print(f"Found {len(c_files)} C files and {len(h_files)} header files")
    
    # Ensure tests directory exists
    os.makedirs('tests/generated', exist_ok=True)
    
    generated_files = []
    
    for c_file in c_files:
        print(f"Processing {c_file}...")
        
        # Read source code for this file
        source_code = read_source_file(c_file, h_files)
        if not source_code:
            print(f"No source code found for {c_file}")
            continue
        
        # Generate prompt
        prompt = generate_test_prompt(source_code, issue_title, issue_body)
        
        print(f"Generating tests for {c_file} with Gemini AI...")
        
        try:
            response = model.generate_content(prompt)
            test_code = response.text
            
            # Clean up the response (remove markdown code blocks if present)
            if '```c' in test_code:
                test_code = test_code.split('```c')[1].split('```')[0]
            elif '```' in test_code:
                test_code = test_code.split('```')[1].split('```')[0]
            
            # Write generated tests
            base_name = os.path.splitext(c_file)[0]
            output_file = f'tests/generated/{base_name}_test.c'
            with open(output_file, 'w') as f:
                f.write(test_code)
            
            generated_files.append(output_file)
            print(f"Tests generated successfully: {output_file}")
            print(f"Generated {len(test_code)} characters of test code")
            
        except Exception as e:
            print(f"Error generating tests for {c_file}: {e}")
            continue
    
    if generated_files:
        print(f"Total test files generated: {len(generated_files)}")
        for f in generated_files:
            print(f"  - {f}")
    else:
        print("No test files were generated")
        exit(1)

if __name__ == "__main__":
    main()
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

def extract_functions_with_docs(source_code):
    """Extract function signatures with preceding documentation and behavior"""
    functions = []
    lines = source_code.split('\n')
    i = 0
    while i < len(lines):
        line = lines[i].strip()
        # Look for function signatures
        if re.match(r'^\w+\s+\w+\s*\([^)]*\)\s*\{', line):
            # Extract function signature
            func_match = re.match(r'(\w+\s+\w+\s*\([^)]*\))\s*\{', line)
            if func_match:
                func_sig = func_match.group(1)
                # Look for preceding comments and behavior (up to 10 lines back)
                docs = []
                behavior = ""
                for j in range(max(0, i-10), i):
                    stripped = lines[j].strip()
                    if stripped.startswith('//') or stripped.startswith('/*'):
                        docs.append(stripped)
                        if 'Behavior:' in stripped:
                            behavior = stripped.replace('// Behavior:', '').strip()
                doc_string = '\n'.join(docs) if docs else "No documentation found"
                functions.append(f"Function: {func_sig}\nDocumentation: {doc_string}\nBehavior: {behavior}")
        i += 1
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

    FUNCTION BEHAVIOR FROM CODE:
    Use the Behavior information provided for each function to create appropriate test expectations.
    Pay special attention to return types and expected values based on the documented behavior.

    RETURN TYPE AWARENESS:
    - Float-returning functions: Use TEST_ASSERT_FLOAT_WITHIN for comparisons
    - Int-returning functions: Use TEST_ASSERT_EQUAL for exact matches
    - Boolean logic functions: Use TEST_ASSERT_TRUE/TEST_ASSERT_FALSE appropriately

    COMMON MISTAKES TO AVOID:
    - Redefining existing functions (causes linker errors)
    - Using non-existent Unity macros (causes compilation errors)  
    - Including mocking code without CMock (causes linker errors)
    - Ignoring the documented behavior of functions
    - Incorrect return type assumptions (float vs int)

    OUTPUT REQUIREMENTS:
    - Must be compilable with gcc and Unity framework
    - Must follow standard Unity test structure
    - Must use only the assertions listed above
    - Must have correct expectations based on the documented function behavior
    """
    functions = extract_functions_with_docs(source_code)
    
    prompt = f"""
    {constraints}
TASK: Generate comprehensive unit tests for C code using the Unity testing framework.

SOURCE CODE:
{source_code}

FUNCTIONS WITH DOCUMENTATION:
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
7. Generate tests for ALL functions listed above - do not skip any functions

OUTPUT FORMAT:
- Complete C file with Unity tests
- Include #include directives for necessary headers
- Use TEST_ASSERT_* macros appropriately
- Group related tests in test suites
- Include a main function that runs ALL test functions

Generate the complete test file:
```c
"""
    return prompt

def validate_and_fix_test_code(test_code):
    """Validate the generated test code and fix common issues"""
    lines = test_code.split('\n')
    
    # Check if main function exists
    has_main = any('int main' in line for line in lines)
    
    # Extract test function names
    test_functions = []
    for line in lines:
        if line.strip().startswith('void test_') and '(' in line:
            func_name = line.split('(')[0].strip()
            test_functions.append(func_name)
    
    if not has_main and test_functions:
        # Add a standard main function
        main_code = f"""

int main(void) {{
    UNITY_BEGIN();
"""
        for func in test_functions:
            main_code += f"    RUN_TEST({func});\n"
        main_code += "    return UNITY_END();\n}\n"
        
        test_code += main_code
    
    return test_code

def main():
    api_key = os.environ.get('GEMINI_API_KEY')
    if not api_key:
        print("Error: GEMINI_API_KEY environment variable not set")
        exit(1)
    
    issue_title = os.environ.get('ISSUE_TITLE', 'Generate unit tests')
    issue_body = os.environ.get('ISSUE_BODY', '')
    
    # Configure Gemini
    genai.configure(api_key=api_key)
    model = genai.GenerativeModel('gemini-2.5-pro')
    
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
            
            # Validate and fix the generated code
            test_code = validate_and_fix_test_code(test_code)
            
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
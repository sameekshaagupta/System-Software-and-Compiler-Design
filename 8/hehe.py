import re

# Function to read code from a file
def read_code_from_file(file_name):
    with open(file_name, 'r') as file:
        return file.read()

# Function to write optimized code to a file
def write_code_to_file(file_name, code):
    with open(file_name, 'w') as file:
        file.write(code)

# Algebraic Simplification Optimization
def algebraic_simplification(code):
    # Simplifies expressions like x + 0, x * 1, etc.
    code = re.sub(r'\b(\w+)\s*\+\s*0\b', r'\1', code)
    code = re.sub(r'\b0\s*\+\s*(\w+)\b', r'\1', code)
    code = re.sub(r'\b(\w+)\s*\*\s*1\b', r'\1', code)
    code = re.sub(r'\b1\s*\*\s*(\w+)\b', r'\1', code)
    code = re.sub(r'\b(\w+)\s*-\s*0\b', r'\1', code)
    code = re.sub(r'\b(\w+)\s*/\s*1\b', r'\1', code)
    return code

# Helper function to get the power of 2 if the number is a power of 2, otherwise return -1
def get_power_of_two(num):
    if num > 0 and (num & (num - 1)) == 0:
        return num.bit_length() - 1
    return -1

# Strength Reduction Optimization (for any power of 2)
def strength_reduction(code):
    # Replace multiplications and divisions by powers of 2 with bit shifts
    multiply_pattern = re.compile(r'\b(\w+)\s*\*\s*(\d+)\b')
    divide_pattern = re.compile(r'\b(\w+)\s*/\s*(\d+)\b')

    # Process multiplication by powers of 2
    def multiply_replacer(match):
        variable, multiplier = match.groups()
        multiplier = int(multiplier)
        power = get_power_of_two(multiplier)
        if power != -1:
            return f'{variable} << {power}'
        return match.group(0)

    code = multiply_pattern.sub(multiply_replacer, code)

    # Process division by powers of 2
    def divide_replacer(match):
        variable, divisor = match.groups()
        divisor = int(divisor)
        power = get_power_of_two(divisor)
        if power != -1:
            return f'{variable} >> {power}'
        return match.group(0)

    code = divide_pattern.sub(divide_replacer, code)
    return code

# Constant Folding Optimization
def constant_folding(code):
    # Simplify constant expressions like 3 + 5 or 4 * 2
    pattern = re.compile(r'\b(\d+)\s*([+\-*/])\s*(\d+)\b')

    def evaluate(match):
        left, operator, right = match.groups()
        left, right = int(left), int(right)
        if operator == '+':
            return str(left + right)
        elif operator == '-':
            return str(left - right)
        elif operator == '*':
            return str(left * right)
        elif operator == '/':
            return str(left // right)  # Integer division for simplicity

    return pattern.sub(evaluate, code)

# Main function to optimize code
def optimize_code(choice, input_file, output_file):
    # Read code from input file
    code = read_code_from_file(input_file)

    # Apply chosen optimization
    if choice == 1:
        optimized_code = algebraic_simplification(code)
        print("Algebraic Simplification applied.")
    elif choice == 2:
        optimized_code = strength_reduction(code)
        print("Strength Reduction applied.")
    elif choice == 3:
        optimized_code = constant_folding(code)
        print("Constant Folding applied.")
    elif choice == 4:
        # Apply all optimizations sequentially
        code = algebraic_simplification(code)  # Apply algebraic simplification
        code = constant_folding(code)  # Apply constant folding
        optimized_code = strength_reduction(code)  # Apply strength reduction
        print("Algebraic Simplification, Constant Folding, and Strength Reduction applied.")
    else:
        print("Invalid choice!")
        return

    # Write optimized code to output file
    write_code_to_file(output_file, optimized_code)
    print(f"Optimized code written to {output_file}")

if __name__ == "__main__":
    input_file = 'input.txt'
    output_file = 'output.txt'

    # Menu
    print("Code Optimization Techniques:")
    print("1. Algebraic Simplification")
    print("2. Strength Reduction")
    print("3. Constant Folding")
    print("4. Apply All (Algebraic Simplification, Constant Folding, and Strength Reduction)")
    choice = int(input("Choose an optimization technique (1, 2, 3, or 4): "))

    # Optimize the code based on the user's choice
    optimize_code(choice, input_file, output_file)

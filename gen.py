import random
import math

def sin(x):
    return math.sin(x)

def cos(x):
    return math.cos(x)

def tan(x):
    return math.tan(x)

def log(x):
    return math.log10(x)

def ln(x):
    return math.log(x)

def arcsin(x):
    return math.asin(x)

def arccos(x):
    return math.acos(x)

def arctan(x):
    return math.atan(x)

def arccot(x):
    return math.pi / 2 - math.atan(x)

def arcsec(x):
    return math.acos(1/x)

def arccosec(x):
    return math.asin(1/x)

def fact(x):
    if x < 0 or x != int(x):
        raise ValueError("Argument to fact must be a non-negative integer")
    return math.factorial(int(x))

def gamma(x):
    return math.gamma(x)

def cot(x):
    return 1 / math.tan(x)

def sec(x):
    return 1 / math.cos(x)

def cosec(x):
    return 1 / math.sin(x)

def evaluate_expression(expr, x):
    try:
        return eval(expr)
    except Exception as e:
        return str(e)

def generate_expression():
    functions = ["sin", "cos", "tan", "cot", "sec", "cosec", "arcsin", "arccos", "arctan", "arccot", "arcsec", "arccosec", "ln", "log", "fact", "gamma"]
    operators = ["+", "-", "*", "/", "^"]
    expression = ""
    
    for _ in range(random.randint(1, 5)):  # Number of terms
        if expression and expression[-1] not in operators:
            expression += random.choice(operators)
        
        func = random.choice(functions)
        if func in ["fact", "gamma"]:  # These functions take one argument
            expression += f"{func}(abs({random.uniform(0.1, 10):.2f} * x))"
        else:
            expression += f"{func}({random.uniform(0.1, 10):.2f} * x)"
        
        if random.choice([True, False]):
            expression = f"({expression})"
    
    # Ensure the expression doesn't end with an operator
    while expression and expression[-1] in operators:
        expression = expression[:-1]
    
    return expression

def generate_test_cases(num_cases, x):
    test_cases = []
    for _ in range(num_cases):
        expr = generate_expression()
        result = evaluate_expression(expr.replace("^", "**"), x)
        test_cases.append((expr, result))
    return test_cases

num_cases = 100
x_value = 5.0

test_cases = generate_test_cases(num_cases, x_value)

for i, (expr, result) in enumerate(test_cases):
    print(f"Test Case {i+1}:")
    print(f"Expression: {expr}")
    print(f"Result: {result}")
    print()


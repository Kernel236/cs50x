while True:
    try:
        height = int(input("Height: "))
        if height < 1:
            print("Height must be positive.")
            continue
        if height > 8:
            print("Height must be 8 or less.")
            continue
        break  # Input valido, esci dal loop
    except ValueError:
        print("Only numbers accepted.")


for i in range(height):
    # Print spaces
    for j in range(height - i - 1):
        print(" ", end="")
    # Print left hashes
    for j in range(i + 1):
        print("#", end="")
    # Print gap
    print("  ", end="")
    # Print right hashes
    for j in range(i + 1):
        print("#", end="")
    print()

import matplotlib.pyplot as plt

# Example datapoints (x, y, t)
x = [1, 2, 3, 4, 5]  # x values
y = [2, 3, 4, 5, 6]  # y values
t = [0, 1, 2, 3, 4]  # time or parameter values

# Plotting the parametric graph of x(t) and y(t)
plt.figure(figsize=(10, 6))

# Plot x(t) and y(t)
plt.subplot(1, 2, 1)  # Create a subplot
plt.plot(t, x, label="x(t)", marker='o')
plt.plot(t, y, label="y(t)", marker='x')
plt.xlabel("Time (t)")
plt.ylabel("Values")
plt.title("Parametric Graph of x(t) and y(t)")
plt.legend()

# Parametric plot of x vs. y
plt.subplot(1, 2, 2)  # Create a subplot
plt.plot(x, y, label="Trajectory (x(t), y(t))", color='r', marker='o')
plt.xlabel("x")
plt.ylabel("y")
plt.title("Parametric Plot of x(t) vs y(t)")
plt.legend()

# Display the plots
plt.tight_layout()
plt.show()

## This is ripped from GPT, Plan on getting Arduino 
## to output datapoints in a copy-pasteable format
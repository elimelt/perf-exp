import matplotlib.pyplot as plt
import numpy as np

def plot_results(file1_path, file2_path):
    # Read data from files
    data1 = np.loadtxt(file1_path)
    data2 = np.loadtxt(file2_path)

    # Extract x and y values
    x1, y1 = data1[:, 0], data1[:, 1]
    x2, y2 = data2[:, 0], data2[:, 1]

    # Create the plot
    plt.figure(figsize=(12, 6))
    plt.plot(x1, y1, label='fun1', color='blue')
    plt.plot(x2, y2, label='fun2', color='red')

    # Set labels and title
    plt.xlabel('Input Size (n)')
    plt.ylabel('Execution Time (nanoseconds)')
    plt.title('Execution Time Comparison: fun1 vs fun2')

    # Add legend
    plt.legend()

    # Add grid
    plt.grid(True, linestyle='--', alpha=0.7)

    # Adjust y-axis to start from 0
    plt.ylim(bottom=0)

    # Show the plot
    plt.tight_layout()
    plt.show()

    # Calculate and print some statistics
    print(f"fun1 average time: {np.mean(y1):.2f} ns")
    print(f"fun2 average time: {np.mean(y2):.2f} ns")
    print(f"fun1 max time: {np.max(y1):.2f} ns")
    print(f"fun2 max time: {np.max(y2):.2f} ns")

# Usage
plot_results('fun1_data.txt', 'fun2_data.txt')
import pandas as pd
import glob
import os
import matplotlib.pyplot as plt
import re

def process_files(dir_path, output_csv):
    files = glob.glob(os.path.join(dir_path, "*.dat"))
    all_data = []

    for file in files:
        # Extraer detalles del archivo a partir del nombre del archivo
        match = re.search(r'MM_ejecutable-(\d+)-Hilos-(\d+).dat', os.path.basename(file))
        if match:
            matrix_size = int(match.group(1))
            thread_count = int(match.group(2))
            data = []

            with open(file, 'r') as f:
                for line in f:
                    if line.strip().startswith(':->'):
                        time_us = int(re.search(r'\d+', line).group())
                        data.append(time_us / 1000000.0)  # Convert from µs to seconds

            if data:
                df = pd.DataFrame({
                    'Matrix Size': [matrix_size] * len(data),
                    'Thread Count': [thread_count] * len(data),
                    'Time (s)': data
                })
                all_data.append(df)

    if not all_data:
        print("No valid data found.")
        return

    combined_data = pd.concat(all_data, ignore_index=True)
    combined_data.to_csv(output_csv, index=False)
    print(f"Data saved to {output_csv}")

    # Calculate and plot the mean execution time for each matrix size and thread count combination
    mean_data = combined_data.groupby(['Matrix Size', 'Thread Count'])['Time (s)'].mean().reset_index()

    plt.figure(figsize=(12, 8))
    for (matrix_size, group) in mean_data.groupby('Matrix Size'):
        plt.plot(group['Thread Count'], group['Time (s)'], marker='o', linestyle='-', label=f'Matrix Size {matrix_size}')

    plt.title('Tiempo por Matriz y Cantidad de Hilos')
    plt.xlabel('Contador de Hilos')
    plt.ylabel('Tiempo (s)')
    plt.legend(title='Matrix Size')
    plt.grid(True)
    plt.savefig(os.path.join(dir_path, 'average_execution_times.png'))
    plt.show()

if __name__ == '__main__':
    dir_path = r'F:\Semestre4-2024\SistemasOperativos\Taller-rendimiento\Evaluacion-Rendimiento\datosSO\WIndowsJuan\mm_Transpuesta\mm_Transpuesta'
    output_csv = os.path.join(dir_path, 'average_results.csv')
    process_files(dir_path, output_csv)

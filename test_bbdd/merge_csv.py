import os
import pandas as pd

csv_directory = './data/'
output_directory = './mergeCsv/'

csv_files = os.listdir(csv_directory)

dfs = []

for csv_file in csv_files:
    if csv_file.endswith(".csv"):
        file_path = os.path.join(csv_directory, csv_file)
        df = pd.read_csv(file_path)
        dfs.append(df)

df_merged = pd.concat(dfs, ignore_index=True)

output_path = os.path.join(output_directory, "merged_data.csv")
df_merged.to_csv(output_path, index=False)

print("¡Fusión exitosa! Se ha creado 'merged_data.csv' en el directorio 'mergeCsv'.")

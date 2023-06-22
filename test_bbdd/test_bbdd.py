import pandas as pd
import os

# Cargar el archivo CSV en un DataFrame de Pandas
csv_path = './data/semana23-06.csv'
df = pd.read_csv(csv_path, delimiter=';')

# Crear una lista de sintaxis SQL para actualizar los valores
sql_updates = []
for indice, fila in df.iterrows():
    id = fila['id']  # Nombre de la columna que contiene el ID
    mobile_number = fila['mobile_number']
    mobile_provider = fila['mobile_provider']
    
    sql_update = f"UPDATE product SET mobile_number='{mobile_number}', mobile_provider='{mobile_provider}' WHERE id='{id}';"
    sql_updates.append(sql_update)

sql_path = os.path.join('data', 'update_script.sql')

with open(sql_path, 'w') as archivo:
    archivo.write('\n'.join(sql_updates))

print("Archivo 'update_script.sql' creado exitosamente.")
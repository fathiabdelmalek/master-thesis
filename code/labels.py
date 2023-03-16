import os
import pandas as pd


data_folder_path = 'data/non_labeled'

merged_data = pd.DataFrame()
for folder_name in [f for f in os.listdir(data_folder_path) if os.path.isdir(os.path.join(data_folder_path, f))]:
    folder_path = os.path.join(data_folder_path, folder_name)
    file_names = [f for f in os.listdir(folder_path) if f.endswith('.csv')]
    if not os.path.isdir(f'data/labeled-all/{folder_path}'):
        os.makedirs(f'data/labeled-all/{folder_name}')
    for file_name in file_names:
        name = os.path.splitext(file_name)[0]
        file_path = os.path.join(folder_path, file_name)
        df = pd.read_csv(file_path)
        df = df.drop('user_id', axis=1)
        df['label'] = name
        df.to_csv(f'data/labeled-all/{folder_name}/{name}.csv', index=False)

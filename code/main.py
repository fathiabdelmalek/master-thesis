import os
import pandas as pd


def merge_csv_files(folder_path, output_path):
    merged_data = pd.DataFrame()
    for file_name in os.listdir(folder_path):
        if file_name.endswith('.csv'):
            file_path = os.path.join(folder_path, file_name)
            df = pd.read_csv(file_path)
            merged_data = pd.concat([merged_data, df], ignore_index=True)
    merged_data.to_csv(output_path, index=False)


# for sub_folder_name in os.listdir('data/labeled-characters'):
#     if os.path.isdir(os.path.join('data/labeled-characters', sub_folder_name)):
#         merge_csv_files(os.path.join('data/labeled-characters', sub_folder_name), f'data/all/characters/{sub_folder_name}.csv')
# for sub_folder_name in os.listdir('data/labeled-words'):
#     if os.path.isdir(os.path.join('data/labeled-words', sub_folder_name)):
#         merge_csv_files(os.path.join('data/labeled-words', sub_folder_name), f'data/all/words/{sub_folder_name}.csv')
# for sub_folder_name in os.listdir('data/labeled-dynamic'):
#     if os.path.isdir(os.path.join('data/labeled-dynamic', sub_folder_name)):
#         merge_csv_files(os.path.join('data/labeled-dynamic', sub_folder_name), f'data/all/dynamic/{sub_folder_name}.csv')
# for sub_folder_name in os.listdir('data/labeled-static'):
#     if os.path.isdir(os.path.join('data/labeled-static', sub_folder_name)):
#         merge_csv_files(os.path.join('data/labeled-static', sub_folder_name), f'data/all/static/{sub_folder_name}.csv')
# for sub_folder_name in os.listdir('data/labeled-all'):
#     if os.path.isdir(os.path.join('data/labeled-all', sub_folder_name)):
#         merge_csv_files(os.path.join('data/labeled-all', sub_folder_name), f'data/all/all/{sub_folder_name}.csv')

merge_csv_files('data/all/characters', 'data/all/all-characters.csv')
merge_csv_files('data/all/words', 'data/all/all-words.csv')
merge_csv_files('data/all/dynamic', 'data/all/all-dynamic.csv')
merge_csv_files('data/all/static', 'data/all/all-static.csv')
merge_csv_files('data/all/all', 'data/all/all-all.csv')

merge_csv_files('data/train/characters', 'data/train/train-characters.csv')
merge_csv_files('data/train/words', 'data/train/train-words.csv')
merge_csv_files('data/train/dynamic', 'data/train/train-dynamic.csv')
merge_csv_files('data/train/static', 'data/train/train-static.csv')
merge_csv_files('data/train/all', 'data/train/train-all.csv')

merge_csv_files('data/test/characters', 'data/test/test-characters.csv')
merge_csv_files('data/test/words', 'data/test/test-words.csv')
merge_csv_files('data/test/dynamic', 'data/test/test-dynamic.csv')
merge_csv_files('data/test/static', 'data/test/test-static.csv')
merge_csv_files('data/test/all', 'data/test/test-all.csv')

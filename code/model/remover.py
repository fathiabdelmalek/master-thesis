from pathlib import Path


characters_folder_path = Path('data/labeled-characters')
words_folder_path = Path('data/labeled-words')
dynamic_folder_path = Path('data/labeled-dynamic')
static_folder_path = Path('data/labeled-static')
characters_folder_path_test = Path('data/labeled-characters-test')
words_folder_path_test = Path('data/labeled-words-test')
dynamic_folder_path_test = Path('data/labeled-dynamic-test')
static_folder_path_test = Path('data/labeled-static-test')

words_files_set = ['bad.csv', 'deaf.csv', 'fine.csv', 'good.csv', 'goodbye.csv', 'hello.csv', 'hungry.csv', 'me.csv',
                   'no.csv', 'please.csv', 'sorry.csv', 'thankyou.csv', 'yes.csv', 'you.csv']

dynamic_files_set = ['bad.csv', 'deaf.csv', 'fine.csv', 'good.csv', 'goodbye.csv', 'hello.csv', 'hungry.csv', 'me.csv',
                     'no.csv', 'please.csv', 'sorry.csv', 'thankyou.csv', 'yes.csv', 'you.csv', 'j.csv', 'z.csv']

for folder_path in [characters_folder_path, words_folder_path, dynamic_folder_path, static_folder_path, characters_folder_path_test, words_folder_path_test, dynamic_folder_path_test, static_folder_path_test]:
    for sub_folder_path in folder_path.iterdir():
        if sub_folder_path.is_dir():
            for file_path in sub_folder_path.glob('*.csv'):
                if folder_path == words_folder_path or folder_path == words_folder_path_test:
                    if file_path.name not in words_files_set:
                        try:
                            file_path.unlink()
                        except OSError as e:
                            print(e)
                elif folder_path == dynamic_folder_path or folder_path == dynamic_folder_path_test:
                    if file_path.name not in dynamic_files_set:
                        try:
                            file_path.unlink()
                        except OSError as e:
                            print(e)
                elif folder_path == characters_folder_path or folder_path == characters_folder_path_test:
                    if file_path.name in words_files_set:
                        try:
                            file_path.unlink()
                        except OSError as e:
                            print(e)
                elif folder_path == static_folder_path or folder_path == static_folder_path_test:
                    if file_path.name in dynamic_files_set:
                        try:
                            file_path.unlink()
                        except OSError as e:
                            print(e)

def confronta_file(file1, file2):
    with open(file1, 'r') as f1, open(file2, 'r') as f2:
        righe_file1 = f1.readlines()
        righe_file2 = f2.readlines()

    # Confronta le righe uno per uno
    for i, (riga1, riga2) in enumerate(zip(righe_file1, righe_file2), 1):
        if riga1 != riga2:
            print(f'Riga {i}:')
            print(f'File 1: {riga1.strip()}')
            print(f'File 2: {riga2.strip()}')
            print()

if __name__ == "__main__":
    file1 = "output.txt"
    file2 = "output2.txt"

    confronta_file(file1, file2)


import os

IGNORED_PATHS = {
    "images",
    "frontend/.next",
    "frontend/node_modules",
    "frontend/public",
    "build",
    ".vscode",
    "readme.md",
    "backend/include",
    "merged_project.txt",
    ".gitignore",
    "frontend/.gitignore",
    "frontend/favicon.ico",
    ".git",
    "lk_merge_tool.py",
    "frontend/yarn.lock"
}

ALLOWED_EXTENSIONS = {
    '.py', '.js', '.jsx', '.ts', '.tsx', '.html', '.css', '.scss',
    '.json', '.xml', '.yaml', '.yml', '.java', '.kt', '.dart', '.go',
    '.rs', '.php', '.rb', '.c', '.cpp', '.h', '.hpp', '.swift', '.md', '.c'
}

def get_ignored_paths():
    current_dir = os.getcwd()
    ignored = set()
    for path in IGNORED_PATHS:
        full_path = os.path.abspath(os.path.join(current_dir, path))
        ignored.add(full_path)
    ignored.add(os.path.abspath("project_dump.txt"))
    return ignored

def is_ignored(path, ignored_paths):
    abs_path = os.path.abspath(path)
    for ignored in ignored_paths:
        if abs_path.startswith(ignored):
            return True
    return False

def merge_code():
    ignored_paths = get_ignored_paths()
    output_file = "project_dump.txt"
    
    with open(output_file, 'w', encoding='utf-8') as outfile:
        for root, dirs, files in os.walk(os.getcwd()):
            # Фильтрация директорий для обхода
            dirs[:] = [d for d in dirs if not is_ignored(os.path.join(root, d), ignored_paths)]
            
            for file in files:
                file_path = os.path.join(root, file)
                if is_ignored(file_path, ignored_paths):
                    continue
                
                ext = os.path.splitext(file)[1].lower()
                if ext not in ALLOWED_EXTENSIONS:
                    continue
                
                try:
                    with open(file_path, 'r', encoding='utf-8') as infile:
                        content = infile.read()
                    outfile.write(f"\n\n{'=' * 80}\n// File: {file_path}\n{'=' * 80}\n\n")
                    outfile.write(content)
                except UnicodeDecodeError:
                    continue
                except Exception as e:
                    print(f"Error processing {file_path}: {str(e)}")

if __name__ == "__main__":
    merge_code()
    print("Code merging completed. Check merged_project.txt")
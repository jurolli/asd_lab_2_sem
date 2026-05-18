#!/bin/bash

show_usage() {
    echo "Использование: $0 <директория> <суффикс>"
    echo "Пример: $0 ./documents txt"
    echo ""
    echo "Что делает:"
    echo "  Находит файлы с указанным суффиксом и числом жёстких связей > 1"
    echo "  Создаёт синонимы (жёсткие ссылки), перенося суффикс в начало имени"
    echo "  Пример: file.txt -> txt_file (без точки)"
    exit 1
}

create_synonyms() {
    local dir="$1"
    local suffix="$2"
    local created_count=0

    if [[ ! -d "$dir" ]]; then
        echo "Ошибка: директория '$dir' не существует"
        return 1
    fi

    cd "$dir" || return 1

    local files=( *."$suffix" )

    if [[ ${#files[@]} -eq 1 && ! -f "${files[0]}" ]]; then
        echo "Файлы с суффиксом '.$suffix' не найдены в директории '$dir'"
        return 0
    fi

    echo "Директория: $dir"
    echo "Суффикс: .$suffix"

    for file in *."$suffix"; do
        [[ ! -f "$file" ]] && continue

        local nlinks
        nlinks=$(stat -f "%l" "$file" 2>/dev/null)

        if [[ -z "$nlinks" ]]; then
            echo "Не удалось получить информацию о файле: $file"
            continue
        fi

        echo "Файл: $file (количество связей: $nlinks)"

        if [[ $nlinks -gt 1 ]]; then
            local basename_no_suffix="${file%.$suffix}"
            local new_name="${suffix}_${basename_no_suffix}"

            if [[ -e "$new_name" ]]; then
                echo "Пропуск: '$new_name' уже существует"
                continue
            fi

            if ln "$file" "$new_name" 2>/dev/null; then
                echo "Создан синоним: '$new_name' → '$file'"
                ((created_count++))
            else
                echo "Ошибка при создании ссылки для '$file'"
            fi
        else
            echo "Пропуск: число связей = $nlinks (нужно > 1)"
        fi
        echo ""
    done

    echo "Готово. Создано синонимов: $created_count"

}

if [[ $# -ne 2 ]]; then
    echo "Ошибка: неверное количество аргументов"
    show_usage
fi

create_synonyms "$1" "$2"
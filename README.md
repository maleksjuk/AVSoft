# Тестовое задание AVSoft (Разработчик C/C++)

*Задание выполнено для Unix-систем (стандарт POSIX). Работоспособность проверена на MacOS*

### Задание 1

* Реализовать схему взаимодействия процессов "читатели-писатели" под с использованием соответствующих системных вызовов POSIX и многопоточности, используя thread, event, и mutex. 
* Приоритет может быть любым. 
* Потоки должны разделять общее адресное пространство. 
* Количество читателей, писателей, повторов программы, а также временные задержки, задаются директивами препроцессора. 
* Вывести на экран результат работы читателей и писателей.

Чтобы запустить решение:
```
cd task1
make
./task1
```

### Задание 2

* Разработать приложение, отображающее список подразделений предприятия и его сотрудников в виде дерева. 
* Список должен загружаться из файла формата xml. 
* Должна быть возможность добавления, удаления, редактирования подразделений и сотрудников в них. 
* Программа должна обеспечить возможность отмены и возврата изменений (пока не реализовано)

Решение выполнено как консольное приложение.
*Для работы с файлом формата XML используется решение https://github.com/zeux/pugixml (файлы pugixml.cpp, pugixml.hpp, pugiconfig.hpp)

Чтобы запустить решение:
```
cd task2
make
./task2
```
Далее следовать инструкциям. 

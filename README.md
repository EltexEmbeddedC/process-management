# Управление процессами

## Сборка и запуск

1. Необходимо перейти в корневую директорию и выполнить команду для сборки проекта `make`

2. Исполняемые файлы появятся в папке `bin`

3. Для удаления всех объектных и исполняемых файлов необходимо выполнить команду `make clean`

## Задания

### Задание 1. Реализовать программу, которая порождает процесс. Родительский процесс и дочерний выводят на экран свои `pid`, `ppid`. Затем родительский ждет завершения дочернего и выводит его статус завершения.

**Тестирование**

**Тест 1:**

```
I'm a parent, my pid = 6219, ppid = 3142
I'm a child, my pid = 6220, ppid = 6219
6220 died with code 0
```

**Тест 2:**

```
I'm a parent, my pid = 6299, ppid = 3142
I'm a child, my pid = 6300, ppid = 6299
6300 died with code 0
```

**Тест 3:**

```
I'm a parent, my pid = 6305, ppid = 3142
I'm a child, my pid = 6306, ppid = 6305
6306 died with code 0
```

### Задание 2. Реализовать программу, которая порождает `процесс1` и `процесс2`, ждет завершения дочерних процессов. `Процесс1` в свою очередь порождает `процесс3` и `процесс4` и ждет их завершения. `Процесс2` порождает `процесс5` и ждет его завершения. Все процессы выводят на экран свой `pid`, `ppid`.

**Тест 1:**

```
process0: pid = 8213, ppid = 3142
process1: pid = 8214, ppid = 8213
process2: pid = 8215, ppid = 8213
process3: pid = 8216, ppid = 8214
process5: pid = 8217, ppid = 8215
process4: pid = 8218, ppid = 8214
message from 1: process3 died (pid = 8216)
message from 2: process5 died (pid = 8217)
message from 1: process4 died (pid = 8218)
message from 0: process2 died (pid = 8215)
message from 0: process1 died (pid = 8214)
```

**Тест 2:**

```
process0: pid = 8318, ppid = 3142
process1: pid = 8319, ppid = 8318
process2: pid = 8320, ppid = 8318
process3: pid = 8321, ppid = 8319
process4: pid = 8322, ppid = 8319
message from 1: process3 died (pid = 8321)
process5: pid = 8323, ppid = 8320
message from 1: process4 died (pid = 8322)
message from 2: process5 died (pid = 8323)
message from 0: process1 died (pid = 8319)
message from 0: process2 died (pid = 8320)
```

> [!TIP]
> Как можно заметить, процессы создаются и завершаются в довольно интересном порядке. Однако при этом в каждом случае соблюдается иерархия, описанная в задании, и процессы-родители терпеливо дожидаются завершения жизни своих детей. :blush:

### Задание 3. Реализовать аналог командного интерпретатора bash. При запуске программы пользователю предлагается ввести имя программы и опции запуска программы. Программа порождает процесс и в нем выполняет введенную программу с заданными опциями, ждет завершения дочернего процесса. Снова возвращается к вводу следующей программы. Выход из интерпретатора по команде exit.

Запустим исполняемый файл. Протестируем перемещение между директориями, запуск системных утилит, vim, собственных бинарных файлов. В случае некорректного ввода ошибки выводятся и программа ожидает ввода следющей команды:

```
alexey@shell: /home/alexey/Projects/Eltex/HW/process-management$ зы
exec failed: No such file or directory
alexey@shell: /home/alexey/Projects/Eltex/HW/process-management$ ps
    PID TTY          TIME CMD
   4676 pts/1    00:00:00 bash
   5797 pts/1    00:00:00 task3
   5800 pts/1    00:00:00 ps
alexey@shell: /home/alexey/Projects/Eltex/HW/process-management$ ls
bin  LICENSE  Makefile	README.md  Task1  Task2  Task3
alexey@shell: /home/alexey/Projects/Eltex/HW/process-management$ cat LICENSE
MIT License

Copyright (c) 2024 EltexEmbeddedC

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
alexey@shell: /home/alexey/Projects/Eltex/HW/process-management$ cd hihi
cd failed: No such file or directory
alexey@shell: /home/alexey/Projects/Eltex/HW/process-management$ cd bin
alexey@shell: /home/alexey/Projects/Eltex/HW/process-management/bin$ ./task1
I'm a parent, my pid = 5805, ppid = 5797
I'm a child, my pid = 5806, ppid = 5805
5806 died with code 0
alexey@shell: /home/alexey/Projects/Eltex/HW/process-management/bin$ exit
```

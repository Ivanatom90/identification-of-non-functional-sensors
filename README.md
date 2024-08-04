#Выявление неработоспособных датчиков

##Описание:
Настоящий проект позволяет с использованием архивных данных провести анализ работоспособности датчиков. Настоящий проект позволяет быстро обработать большое количество показаний датчиков и выявить неработоспособные.

##Инструкция по развертыванию:

В корневом каталоге программы должны находиться следующие папки:
- answer — в данной папке по результату работы программы формируется отчетная информация, определяющая состояние датчиков;
- input_data — содержит архивные данные с показаниями датчиков;
- input_names — содержит названия датчиков участвующих в расчете;

##Использовано:
- Стандарт языка С++17;
- Библиотека STL контейнеров;
- Алгоритмы.

##Последовательность действий и требования для запуска программы:
1) В папку  input_data добавить архивные данные с показаниями датчиков в формате .txt
2) После запуска исполняемого файла необходимо ввести номер блока, датчики которого необходимо проверить на работоспособность.
3) Проверка работоспособности датчиков проводится проводиться по наличию показаний датчика и по расчетной погрешности каждого датчика.
4) По окончанию работы программы в папке  answer  формируется отчетная информация, определяющая состояние датчиков. В отчетном документе answer/result.txt появляется список неработоспособных датчиков.  В answer/pogr перечислен список датчиков с указанием их случайной погрешности.

##Программа является моей разработкой

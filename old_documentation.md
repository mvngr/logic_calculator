# Старая версия документации

Классы, методы и переменные, которые использует калькулятор

### MainWindow
Класс отвечает за взаимодействие с пользовательским интерфейсом

Метод | Описание
----------------|----------------------
inputPressed | Обработчик для поля ввода данных, вызывается при нажатии на `enter`
onClicked | Обработчик на кнопки логических операций. Добавляет в поле ввода данных соответствующий символ
bindConnect | Создаёт связи между обработчиком события `onClicked` и нажатой кнопкой
on_compute_clicked | Обработчик нажатия на кнопку `Вычислить`
connectQss | Отвечает за подключение стилей
on_f4_clicked | Обработчик для кнопки `СДНФ`
on_f5_clicked | Обработчик для кнопки `СКНФ`

### InputEditor
Класс отвечает за обработку данных, вводимых в поле ввода данных

Переменная | Описание
----------------|----------------------
input_ | Используется для управления полем ввода данных
v_ | Внутренний массив для хранения данных из поля ввода данных

Метод | Описание
----------------|----------------------
PushBack | Добавляет определенные данные в конец внутреннего массива
toString | Преобразует внутренний массив в строку 
parse | Парсит введенную строку, возвращает в виде переменной ответ, смогло ли произойти чтение
getVars | Добавление в внутренний массив внешние данные
updateInput | Обновляет поле для ввода данных
fillConsts | Заполняет словари заранее подготовленными данными
isValidity | Определяет корректность данных в внутреннем массиве относительно поля ввода данных

### Logic
Класс отвечает за логику выполнения действий

Переменная | Описание
----------------|----------------------
BINARY_OPERATIONS_ | Словарь бинарных операций
BINARY_OPERATIONS_TO_NUM_ | Сопоставление бинарной операции с её внутренним номером (нужно для удобства)
AVIABLE_NAME_OF_VARS_ | Словарь разрешенных имен для логических переменных
vars_ | Массив логических переменных
v_ | Массив строк, разделенных при помощи пробела. Пример: `{"A", "*", "B", "+", "!", "C"}`
map_ | Используется для сопоставления строковых переменных и их аналогов из vars_. `<Название переменной> => <Индекс в массиве объекта>`
ce_ | Используется для управление полем вывода


Метод | Описание
----------------|----------------------
setVars | Добавляет массив логических переменных в внутренний массив
compute | Инициирует вычисления
computeLogicalAction | Инициирует вычисление таблицы истинности
getVarsTitle | Отдает массив имен логических переменных
getVarsData | Отдает массив всех данных из логических переменных
negation | Используется для выполнения отрицания у всей входной строки 
negationFunc | Используется для выполнения отрицания у выражений со скобками во входной строке
binaryOperation | Используется для выполнения входной операции у всей входной строки
fillOperations | Используется для заполнения словарей
showError | Выводит в пользовательский интерфейс сообщения с ошибками
insertWithReplace | Выполняет внедрение логической операции в внутренние массивы взамен переменным(ой) и оператора
fillVars | Добавляет логические переменные в vars_ из строк `v_`
fillMap | Заполняет карту `map_`
isRepeat | Проверяет на повторение названия имен в `vars_`
sortVars | Сортирует массив `vars_` по названиям
makeBoolArrays | Создает массив начальных данных у переменных
findBrackets | Находит выражения в скобках и высчитывает их
subString | Возвращает подстроку из строки
makeSKNF | создает Совершенную Конъюнктивную Нормальную Форму
makeSDNF | создает Совершенную Дизъюнктивную Нормальную Форму



### ContentEditor
Класс отвечает за корректный и удобный вывод чего-либо в поле для вывода

Переменная | Описание
----------------|----------------------
pte_ | Управление полем вывода
cellSize_ | Размеры ячеек в таблице истинности
 
Метод | Описание
----------------|----------------------
printTruthTable | Инициирует вывод таблицы истинности
getSize | Заполняет значения размеров ячеек в таблице истинности `cellSize_`
makeString | Создает строку из повторяющихся amount раз символов segment
makeLine | Создает линию под заголовком
makeTitle | Создает заголовок
makeData | Создает двумерный массив данных `<0/1>`
centerAlign | выравнивает все элементы по центру своей ячейки
printSKNF | выводит Совершенную Конъюнктивную Нормальную Форму
printSDNF | выводит Совершенную Дизъюнктивную Нормальную Форму
 
### Variable
Класс логических переменных

Переменная | Описание
----------------|----------------------
name_ | Имя логической переменной
vars_ | Принимаемые значения

Метод | Описание
----------------|----------------------
conjunction | Конъюнкция с переменной `other`
disjunction | Дизъюнкция с переменной `other`
implication | Импликация с переменной `other`
converse | Обратная импликация с переменной `other`
notAnd | Штрих Шеффера с переменной `other`
notOr | Стрелка Пирса с переменной `other`
exclusiveDisjunction | Исключающее ИЛИ с переменной `other`
equivalent | Эквиваленция с переменной `other`
negation | Отрицание самой переменной
setName | Задает имя `name_` как у переменной `name`
setVars | Задает принимаемые значения `vars_` как у массива `vars`, либо генерирует их, основываясь на индексе элемента и количестве элементов
getName | Отдает значение `name_`
getVars | Отдает значение `vars_`
debugVars | Выводит значения `vars_` в консоль (Не используется)
pow2 | Возвращает степень числа два
makeName | Создает строку из двух названий переменных и операции между ними
 

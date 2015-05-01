# Модули LEGO для языка RCML
-------------------------------
Данный модули позволяют программировать **Lego** роботов на RCML, работающих под управлением **Lego блока EV3 или NXT**. Программа на RCML исполняется на ПК, связь с EV3 или NXT осуществляется через **Bluetooth**.<br>
EV3 или NXT предварительно должен быть сопряжен с компьютером по Bluetooth.<br>
Модуль имеет конфигурационный файл, в котором указывается COM-порт, осуществляющий коммуникацию с EV3 или NXT. Номер COM-порта можно посмотреть в свойствах Bluetooth устройства на ПК.

*Например модуль EV3 или NXT подключен к порту COM3, тогда в config.ini будет иметь следующее содержимое:*
```ini
    [connections]
    connection = COM3
```
*Стоит обратить внимание, что config.ini должен находиться в одной директории с файлом модуля.*


####Особенности входящих значений для функций модулей:
Для обращения к моторам A,B,C,D используются буквы "A","B","C" и "D" соответственно;<br>
Для обращения к датчикам под номерами 1,2,3,4 используются соответствующие номера;<br>
На параметры функций **speed** и **percent** наложены следующие ограничения:
- **speed** принимает значения [-100;100];
- **percent** принимает значения [0;100].

*При превышении указанных ограничений вызываемая функция бросает исключение, которое можно обработать с помошью конструкции языка RCML try/catch.*

## Модуль для Lego EV3
-----------------------------------

####Доступные функции робота:
Определение  | Описание | Пример
------------  | -----------------  | ---------------
motorSetSpeed(**motor**, **speed**)  | Задает мотору **motor** скорость **speed** |  @lr->motorSetSpeed ("B",20); Задает мотору **B** скорость 20.
motorOff(**motor**) | Выключает мотор **motor** без использования тормозов, т.е. мотор остановится не сразу. |  @lr->motorOff("C"); Остановит мотор **C**.
motorBreak(**motor**) | Останавливает мотор **motor**, используя тормоза. Мгновенная остановка. |  @lr->motorBreak("D"); Остановит мотор **D**.
motorSetDirection(**motor**, **direction**) | Устанавливает направление мотора **motor**. **direction**=0 задает направление мотора "назад". **direction** != 0 задает направление мотора "вперед" |  @lr->motorSetDirection("A",0); Установит направление мотора **А** "назад". 
motorGetDirection(**motor**) | Возвращает 1 если направление мотора **motor** установлено как "вперед", возвращает 0 если направление мотора **motor** установлено как "назад". Мотор остановится не сразу. |  RecievedDirection = @lr->motorGetDirection("C"); 
motorMoveTo(**motor**, **speed**, **position**,**brake**) | Перемещает мотор **motor** в положение **position** со скоростью **speed**. **brake** = 0 - не использовать тормоз, **brake** != 0 - использовать тормоз. |  @lr->motorMoveTo("B",10,200,0); Переместит мотор **B** в позицию 200 со скоростью 10 не используя тормоз.
motorGetTacho(**motor**) | Возвращает позицию мотора **motor**. |  RecievedTacho = @lr->motorGetTacho("C"); 
motorResetTacho(**motor**) | Устанавливает текущую позицию мотора **motor** как нулевую. |  @lr->motorResetTacho("C"); 
waitMotorToStop(**motor**) | Ждет пока остановится мотор **motor**. |  @lr->waitMotorToStop("C");
waitMultiMotorsToStop( **motorA**,**motorB**, **motorC**,**motorD**) | Ждет пока остановится несколько моторов. Если **motor** != 0, то ждет остановки, если **motor** = 0, то не ждет. |  @lr->waitMultiMotorsToStop(1,0,0,1); Ждет пока остановятся моторы **А** и **D**.
setTrackVehicle( **motorLeft**,**motorRight**, **LeftReverse**,**RightReverse**) | Логически соединяет 2 мотора **motorLeft** и **motorRight** в *Track Vehicle* (гусеничный транспорт). Позволяет обращаться к этим моторам как к единому целому и открывает дополнительные функции управления Track Vehicle, имеющие префикс *trackVehicle*. Left и Right Reverse при значении != 0 задает моторам обратное направление. |  @lr->setTrackVehicle("B","C",1,0); Логически соединяет моторы **B** и **C** в Track, при этом мотор **B** изменяет свое направление на обратное.
trackVehicleBackward( **speed**) | Track Vehicle движется назад со скоростью **speed**. |  @lr->trackVehicleBackward(20); 
trackVehicleForward( **speed**) | Track Vehicle движется вперед со скоростью **speed**. |  @lr->trackVehicleForward(40); 
trackVehicleOff() | Выключает моторы Track Vehicle. Моторы остановится не сразу. |  @lr->trackVehicleOff();
trackVehicleBrake() | Останавливает моторы Track Vehicle, используя тормоза. |  @lr->trackVehicleBrake();
trackVehicleSpinLeft(**speed**) | Track Vehicle поворачивается влево вокруг своей вертикальной оси. |  @lr->trackVehicleSpinLeft(10); 
trackVehicleSpinRight(**speed**) | Track Vehicle поворачивается вправо вокруг своей вертикальной оси. |  @lr->trackVehicleSpinRight(90);
trackVehicleTurnLeftForward( **speed**, **percent**) |  Track Vehicle поворачивает влево, двигаясь вперед. Правый мотор будет иметь со скорость **speed**, а левый **(speed - speed*percent/100)**. Таким образом если **percent**=0 то моторы будут иметь одинковую скорость, а при **percent**=100 левый мотор будет иметь нулевую скорость.  |  @lr->trackVehicleTurnLeftForward(20, 50);
trackVehicleTurnRightForward( **speed**, **percent**) | Track Vehicle поворачивает влево, двигаясь вперед. Левый мотор будет иметь со скорость **speed**, а правый **(speed - speed*percent/100)**. Таким образом если **percent**=0 то моторы будут иметь одинковую скорость, а при **percent**=100 правый мотор будет иметь нулевую скорость. |  @lr->trackVehicleTurnRightForward(10, 90);
trackVehicleTurnLeftReverse( **speed**, **percent**)  | Track Vehicle поворачивает влево, двигаясь назад. Скорость правого мотора равна **speed**,  а левого **(speed - speed*percent/100)** |  @lr->trackVehicleTurnLeftReverse(10,20); 
trackVehicleTurnRightReverse( **speed**, **percent**)  | Track Vehicle поворачивает вправо, двигаясь назад. Скорость левого мотора равна **speed**,  а правого **(speed - speed*percent/100)** |  @lr->trackVehicleTurnRightReverse(50,50); 
readSensor( **sensor**, **mode**)  | Считывает показания сенсора под номером **sensor** в режиме **mode**. Для разных датчиков существует разное количество режимов. |  @lr->readSensor(2,1); Считывает показания датчика подключенного к порту 2 в режиме 1.


####Режимы датчиков:

Для данного модуля доступно подключение датчиков 8 типов.

Датчик | Режим 
------------  | -------------
Ультразвуковой | 1 - режим определения расстояния в сантиметрах<br> 2 - режим определения расстояния в дюймах<br> 3 - режим прослушивания
Инфракрасный | 1 - режим определения расстояния<br> 2 - режим определения местоположения инфракрасного дистанционного пульта<br> 3- режим определения нажатия кнопок на инфракрасном пульте
Цветовой | 1 - режим определения интенсивности света<br> 2 - режим определения цвета *(см. таблицу цветов)*<br> 3- режим определения raw значения отраженного света <br> 4 - режим определения отраженного света
Гироскопический | 1 - режим определения угла в градусах<br> 2 - режим определения угловой скорости в градусах в секунду 
Датчик нажатия | 1 - режим отслеживания нажатия<br> 2 - режим вывода количества нажатий
Датчик Температуры | 1 - режим измерения температуры по шкале Цельсия<br> 2 - режим измерения температуры по шкале  Фаренгейта
Датчик Звука | 1 - режим измерения громкости звука в dB<br> 2 - режим измерения громкости звука в dBA
Датчик Света | 1 - режим измерения интенсивности<br> 2 - режим измерения отраженного света

####Таблица цветов:
Цвет | Возвращаемое значение
------- |:---------:
Черный | 1
Синий | 2
Зеленый | 3
Желтый | 4
Красный | 5
Белый | 6
Коричневый | 7


####Оси робота:

Ось| Верхняя граница | Нижняя граница | Описание 
------------  | :-----------------: | :--------------: | ---------------
locked | 1 | 0 | Бинарная ось. Если её значение равно 1, то робот считается заблокированным и игнорирует изменение значений по любым другим осям.
speedMotorA | 100 | -100 | Значение оси задает скорость мотора подключенного к порту **A**.
speedMotorB | 100 | -100 | Значение оси задает скорость мотора подключенного к порту **B**.
speedMotorC | 100 | -100 | Значение оси задает скорость мотора подключенного к порту **C**.
speedMotorD | 100 | -100 | Значение оси задает скорость мотора подключенного к порту **D**.
moveMotorA | 1000 | -1000 | Значение оси задает позицию на которую повернется мотор **A** со скоростью 50.
moveMotorB | 1000 | -1000 | Значение оси задает позицию на которую повернется мотор **B** со скоростью 50.
moveMotorC | 1000 | -1000 | Значение оси задает позицию на которую повернется мотор **C** со скоростью 50.
moveMotorD | 1000 | -1000 | Значение оси задает позицию на которую повернется мотор **D** со скоростью 50.
straight | 100 | -100 | Значение оси задает скорость с которой прямолинейно перемещается Track Vehicle.
rotation | 100 | -100 | Значение оси задает скорость с  которой Track Vehicle вращается вокруг своей вертикальной оси.

*Track Vehicle должен быть инициализирован прежде чем будет задействована ось straight или rotation, т.е. до включения режима ручного управления!*


## Модуль для Lego NXT
-----------------------------------

*NXT блок в отличии от EV3 имеет только три мотора, поэтому для обращения к его моторам A,B,C используются буквы "A","B" и "C" соответственно.<br>*

####Доступные функции робота:
Определение  | Описание | Пример
------------  | -----------------  | ---------------
motorSetSpeed(**motor**, **speed**)  | Задает мотору **motor** скорость **speed** |  @lr->motorSetSpeed ("B",20); Задает мотору **B** скорость 20.
motorOff(**motor**) | Выключает мотор **motor** без использования тормозов, т.е. мотор остановится не сразу. |  @lr->motorOff("C"); Остановит мотор **C**.
motorBreak(**motor**) | Останавливает мотор **motor**, используя тормоза. Мгновенная остановка. |  @lr->motorBreak("A"); Остановит мотор **A**.
motorSetDirection(**motor**, **direction**) | Устанавливает направление мотора **motor**. **direction**=0 задает направление мотора "назад". **direction** != 0 задает направление мотора "вперед" |  @lr->motorSetDirection("A",0); Установит направление мотора **А** "назад". 
motorGetDirection(**motor**) | Возвращает 1 если направление мотора **motor** установлено как "вперед", возвращает 0 если направление мотора **motor** установлено как "назад". Мотор остановится не сразу. |  RecievedDirection = @lr->motorGetDirection("C"); 
motorMoveTo(**motor**, **speed**, **position**,**brake**) | Перемещает мотор **motor** в положение **position** со скоростью **speed**. **brake** = 0 - не использовать тормоз, **brake** != 0 - использовать тормоз. |  @lr->motorMoveTo("B",10,200,0); Переместит мотор **B** в позицию 200 со скоростью 10 не используя тормоз.
motorGetTacho(**motor**) | Возвращает позицию мотора **motor**. |  RecievedTacho = @lr->motorGetTacho("C"); 
motorResetTacho(**motor**) | Устанавливает текущую позицию мотора **motor** как нулевую. |  @lr->motorResetTacho("C"); 
waitMotorToStop(**motor**) | Ждет пока остановится мотор **motor**. |  @lr->waitMotorToStop("C");
waitMultiMotorsToStop( **motorA**,**motorB**, **motorC**) | Ждет пока остановится несколько моторов. Если **motor** != 0, то ждет остановки, если **motor** = 0, то не ждет. |  @lr->waitMultiMotorsToStop(1,0,1); Ждет пока остановятся моторы **А** и **С**.
setTrackVehicle( **motorLeft**,**motorRight**, **LeftReverse**,**RightReverse**) | Логически соединяет 2 мотора **motorLeft** и **motorRight** в *Track Vehicle* (гусеничный транспорт). Позволяет обращаться к этим моторам как к единому целому и открывает дополнительные функции управления Track Vehicle, имеющие префикс *trackVehicle*. Left и Right Reverse при значении != 0 задает моторам обратное направление. |  @lr->setTrackVehicle("B","C",1,0); Логически соединяет моторы **B** и **C** в Track, при этом мотор **B** изменяет свое направление на обратное.
trackVehicleBackward( **speed**) | Track Vehicle движется назад со скоростью **speed**. |  @lr->trackVehicleBackward(20); 
trackVehicleForward( **speed**) | Track Vehicle движется вперед со скоростью **speed**. |  @lr->trackVehicleForward(40); 
trackVehicleOff() | Выключает моторы Track Vehicle. Моторы остановится не сразу. |  @lr->trackVehicleOff();
trackVehicleBrake() | Останавливает моторы Track Vehicle, используя тормоза. |  @lr->trackVehicleBrake();
trackVehicleSpinLeft(**speed**) | Track Vehicle поворачивается влево вокруг своей вертикальной оси. |  @lr->trackVehicleSpinLeft(10); 
trackVehicleSpinRight(**speed**) | Track Vehicle поворачивается вправо вокруг своей вертикальной оси. |  @lr->trackVehicleSpinRight(90);
trackVehicleTurnLeftForward( **speed**, **percent**) |  Track Vehicle поворачивает влево, двигаясь вперед. Правый мотор будет иметь со скорость **speed**, а левый **(speed - speed*percent/100)**. Таким образом если **percent**=0 то моторы будут иметь одинковую скорость, а при **percent**=100 левый мотор будет иметь нулевую скорость.  |  @lr->trackVehicleTurnLeftForward(20, 50);
trackVehicleTurnRightForward( **speed**, **percent**) | Track Vehicle поворачивает влево, двигаясь вперед. Левый мотор будет иметь со скорость **speed**, а правый **(speed - speed*percent/100)**. Таким образом если **percent**=0 то моторы будут иметь одинковую скорость, а при **percent**=100 правый мотор будет иметь нулевую скорость. |  @lr->trackVehicleTurnRightForward(10, 90);
trackVehicleTurnLeftReverse( **speed**, **percent**)  | Track Vehicle поворачивает влево, двигаясь назад. Скорость правого мотора равна **speed**,  а левого **(speed - speed*percent/100)** |  @lr->trackVehicleTurnLeftReverse(10,20); 
trackVehicleTurnRightReverse( **speed**, **percent**)  | Track Vehicle поворачивает вправо, двигаясь назад. Скорость левого мотора равна **speed**,  а правого **(speed - speed*percent/100)** |  @lr->trackVehicleTurnRightReverse(50,50); 


####Функции опроса датчиков:
Определение  | Описание | Режимы
------------  | -----------------  | ---------------
readHiTecColor( **port**, **mode**)  | Считывает показания HiTecColor сенсора на порту **port** в режиме **mode**. | 1 - Возвращает значение красного цвета [0;255]<br> 2 - Возвращает значение зеленого цвета [0;255]<br> 3 - Возвращает значение синего цвета [0;255]<br>
readHiTecCompass( **port**)  | Считывает показания HiTecCompass сенсора на порту **port**. | Возвращает значение в градусах
readHiTecGyro( **port**)  | Считывает показания HiTecGyro сенсора на порту **port**. | Возвращает угловое ускорение в градусах в секунду
readHiTecTilt( **port**, **mode**)  | Считывает показания HiTecTilt сенсора на порту **port** в режиме **mode**. | 1 - Возвращает целочисленное значение положения датчика по оси x<br> 2 - Возвращает целочисленное  значение положения датчика по оси y<br> 3 - Возвращает целочисленное значение положения датчика по оси z<br>
readNXTColor( **port**, **mode**)  | Считывает показания NXTColor сенсора на порту **port** в режиме **mode**. | 1 - Возвращат целочисленное значение, соответствующее таблице цветов<br> 2 - Возвращает интенсивность красного цвета в процентах<br> 3 - Возвращает интенсивность зеленого цвета в процентах<br> 4 - Возвращает интенсивность синего цвета в процентах<br> 5 - Возвращает интенсивность света в процентах<br>
readNXTLight( **port**, **mode**)  | Считывает показания NXTLight сенсора на порту **port** в режиме **mode**. | 1 - Возвращает интенсивность света в виде целочисленного значения<br> 2 - Возвращает интенсивность света в процентах<br> 
readNXTSonar( **port**, **mode**)  | Считывает показания NXTSonar сенсора на порту **port** в режиме **mode**. | 1 - режим определения расстояния в сантиметрах<br> 2 - режим определения расстояния в дюймах<br>
readNXTSound( **port**, **mode**)  | Считывает показания NXTSound сенсора на порту **port** в режиме **mode**. | 1 - режим измерения громкости звука в dB<br> 2 - режим измерения громкости звука в dBA
readNXTTouch( **port**, **mode**)  | Считывает показания NXTTouch сенсора на порту **port** в режиме **mode**. | 1 - режим отслеживания нажатия<br> 2 - режим вывода количества нажатий
readRCXLight( **port**, **mode**)  | Считывает показания RCXLight сенсора на порту **port** в режиме **mode**. | 1 - режим измерения интенсивности<br> 2 - режим измерения отраженного света
readRCXRotation( **port**)  | Считывает показания RCXRotation сенсора на порту **port**. | Возвращает шаг поворота [-16;+16]
readRCXTemperature( **port**, **mode**)  | Считывает показания RCXTemperature сенсора на порту **port** в режиме **mode**. | 1 - режим измерения температуры по шкале Цельсия<br> 2 - режим измерения температуры по шкале  Фаренгейта

####Таблица цветов:
Цвет | Возвращаемое значение
------- |:---------:
Черный | 1
Синий | 2
Зеленый | 3
Желтый | 4
Красный | 5
Белый | 6

####Оси робота:

Ось| Верхняя граница | Нижняя граница | Описание 
------------  | :-----------------: | :--------------: | ---------------
locked | 1 | 0 | Бинарная ось. Если её значение равно 1, то робот считается заблокированным и игнорирует изменение значений по любым другим осям.
speedMotorA | 100 | -100 | Значение оси задает скорость мотора подключенного к порту **A**.
speedMotorB | 100 | -100 | Значение оси задает скорость мотора подключенного к порту **B**.
speedMotorC | 100 | -100 | Значение оси задает скорость мотора подключенного к порту **C**.
moveMotorA | 1000 | -1000 | Значение оси задает позицию на которую повернется мотор **A** со скоростью 50.
moveMotorB | 1000 | -1000 | Значение оси задает позицию на которую повернется мотор **B** со скоростью 50.
moveMotorC | 1000 | -1000 | Значение оси задает позицию на которую повернется мотор **C** со скоростью 50.
straight | 100 | -100 | Значение оси задает скорость с которой прямолинейно перемещается Track Vehicle.
rotation | 100 | -100 | Значение оси задает скорость с  которой Track Vehicle вращается вокруг своей вертикальной оси.

*Track Vehicle должен быть инициализирован прежде чем будет задействована ось straight или rotation, т.е. до включения режима ручного управления!*


####Компиляция
Для компиляции модуля потребуются библиотеки:
- [SimpleIni](https://github.com/brofield/simpleini)
- [MonoBrick Communication Library](http://www.monobrick.dk/software/monobrick/)

Библиотека MonoBrick Communication Library используется в отличающемся от оригинала виде и находится в папке lego_communication_library.


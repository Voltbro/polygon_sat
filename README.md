# Спутник полигона

Пример Arduino прошикви для платы спутника "Полигон"


### Управление спутником
Спутник получает команды через радио модуль HC-12 и далее через интерфейс Serial1

### Команды
* Положительное целое число n -- спутник "едет" совершая n оборотов серво привода 
* Отрицательное число n -- спутник "едет" назад совершая n оборотов серво привода 
* Ноль -- остановка спутника

Разделитель команд, символы новой строчки (\r\n)

Если спутник достиг заданной точки, то он выдает в радио канал сообщение "STOP". Если сработал один из концевых выключателей, спутник выдает сообщения "END_SWITCH1" или "END_SWITCH2" и откатывается из крайней точки.

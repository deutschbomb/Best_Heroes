# Best_Heroes
Оптимальный выбор 1х1.

Дан набор персонажей с произвольно заданными характеристиками, не менее 10 персонажей.
Соперник выбрал одного персонажа.
Выбрать среди оставшихся персонажей тех, кто побеждает персонажа соперника с указанием времени сражения и процента оставшегося здоровья.
В случае если таких персонажей несколько, то ранжировать их по: времени сражения или проценту (от первоначального) оставшегося здоровья.
Вариант ранжирования (сортировки задается) как входной параметр.


1)	Персонаж обладает несколькими характеристиками:
-	Количество наносимого им урона противнику в секунду. Персонаж наносит урон все время, кроме времени, на которое он выведен из строя.
	Если персонаж наносит урон нескольким соперникам, указанный урон наносится каждому.
-	Количество соперников, которым наносится урон. Не более 3.
-	Здоровье персонажа. Наносимый урон вычитается из текущего здоровья, при достижении значения 0, персонаж выбывает.
-	Способность выводить из строя одного соперника. Задается двумя значениями в секундах:
первое - на которое соперник выводится из строя,
второе – интервал вывода из строя. Второе как минимум в двое больше первого.
-	 Персонаж выводит из строя, как только удается это сделать.
2)	Персонажи могут сражаться один против одного, и в командах по 3 персонажа.
Победой команды считается, когда все персонажи противоположной команды выбыли.
Каждого персонажа можно выбирать только один раз (не зависимо от того, в какой команде уже выбран этот персонаж).

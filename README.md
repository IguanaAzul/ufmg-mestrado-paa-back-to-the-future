
# Back to the Future
#### Exercício de Projeto e Análise de Algoritmos

##### [Enunciado Beecrowd (URI)](https://www.beecrowd.com.br/judge/en/problems/view/1447):

A group of friends decided to go to Germany to cheer for the Brazilian Team in its glorious journey toward ‘hexa’. As the tickets and the stay are very expensive, each one brought the money they thought was sufficient to spend the month with confort e return home with no problem.

But, after the nice campaign of Brazil, the group was forced to spend the money they had saved with the famous German beer. The consequences were terrible. After drinking too much, all of them got caught sleeping on the streets and them all received heavy fines. Besides, all of them lost their tickets to get back. Suddenly, they find out they need to get back home spending the least possible amount o money.

Analyzing the available routes in the airport, the friends noticed that in all the routes the amount of available sits is always the same. But the price between one city and another one varies a lot. Scared with the possibility of not founding enough sits on the planes so all of them could get back, and worried about the money they need to spend, the friends asked for your help.

### Input
The input contains several test cases. Each test case starts with 2 positive integers **N** (2 ≤ **N** ≤ 100) and **M** (1 ≤ **M** ≤ 5000), where **N** is the number of cities that belong to **M** considered routes. The friends want to go from city 1 to city **N**.

The next **M** lines contains triple integers **A**, **B**, and **C** describing the plane route (**A** and **B**) and the price of the ticket per person (**C**). The values of **A** and **B** are between 1 and **N**. The routes are bidirectional (that is, there's a flight from **A** to **B** and from **B** to **A** with price **C**) and there will be only one route between two cities. In the next line there are the integers, **D** and **K**, where **D** is the number of friends and **K** is the number of free sits on each flight. Each route can be utilized only once.

### Output
For each test, print the line "Instancia **k**", where **k** is the number of the current test case. Besides, print the least amount of money the friends will pay to get back to Brazil (1015). If there's no way to pick up a set of flights that will take all home, print "impossivel" (impossible).

Print a blank line after each test.

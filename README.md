threads_safe
Atomic - семантика операций store, exchange, load, fetch_add
Пример на github 
У атомиков есть перегруженные операции = и ++ на замену store и fetch_add
locked = 0 вместо locked.store(0)
next_free_ticket++ вместо next_free_ticket.fetch_add(1)


Exchange - атомарный обмен содержимого ячейки памяти. 
Утверждается, что если у нас есть атомарный exchange то мы можем сделать алгоритм взаимного исключения для произвольного числа потоков и оперировать всего лишь одной ячейкой памяти.
Тут есть проблема, этот способ не гарантирует что разные потоки не будут голодать. (какому-то потоку будет очень долго не везти) То есть не гарантируется прогресс для каждого потока. Чтоб достичь решения используется fetch_add.

fetch_add - атомарный инкремент. 

У обоих примеров можно наглядно заметить пустые строки в цикле, что говорит о растрате ресурсов процессора, в данном случае можно улучшить с помощью вызова std::this_thread::yield() который говорит о передаче работы потока следующему.

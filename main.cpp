#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
#include "Factory.h"
#include "Product.h"
#include "Vehicle.h"
#include "Warehouse.h"

using namespace std;

void foo(Warehouse w, Factory f, Vehicle v);
auto a = 550;
mutex m;

int main()
{
	Warehouse w(1000);
	Product p("Milk", 1000, "Cartoon");
	Factory f(p, 150);
	Vehicle v("Gazel", 270);
	foo(w, f, v);
	return 0;
}

void foo(Warehouse w, Factory f, Vehicle v)
{
	thread t1;
	while (true)
	{
		if (a >= 950  || a + f.GetfactoryItemPerHour() > w.GetwarehouseCapacity())
		{
			if (t1.joinable() == true) //Защита от повторного вызова существующего потока
			{
				cout << "Potok closed" << endl;
				t1.detach();
			}

			cout << "Potok open" << endl;
			t1 = (thread([&]()
				{
					while (a >= 0)
					{
						if (a - v.GetvehicleCapacity() < 0)
						{
							cout << "Potok closed" << endl;
							t1.detach();
							break;
						}
						this_thread::sleep_for(chrono::milliseconds(1500));
						m.lock();
						cout << "......Export items......" << endl;
						a -= v.GetvehicleCapacity();
						cout << "Items in Warehouse: " << a << endl;
						m.unlock();
					}
				}));
		}
		this_thread::sleep_for(chrono::milliseconds(2000));
		m.lock();
		cout << "......Import items......" << endl;
		a += f.GetfactoryItemPerHour();
		cout << "Items in Warehouse: " << a << endl;
		m.unlock();
		
	}
	t1.join();
}
#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
#include <vector>
#include "Factory.h"
#include "Product.h"
#include "Vehicle.h"
#include "Warehouse.h"

using namespace std;

void foo(Warehouse &w, Factory &f, vector<Vehicle> &v);
int a = 550;
mutex m;

int main()
{
	Warehouse w(1500);
	Product p("Milk", 1000, "Cartoon");
	Factory f(p, 150);
	vector<Vehicle> v = { Vehicle ("Gazel", 270), Vehicle("Kamaz", 500) };
	foo(w, f, v);
	return 0;
}

void foo(Warehouse &w, Factory &f, vector<Vehicle> &v)
{
	thread t1;
	while (true)
	{
		if (a >= 1425  || a + f.GetfactoryItemPerHour() > w.GetwarehouseCapacity())
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
						for (auto &el : v)
						{
							while (a - el.GetvehicleCapacity() < 0)
							{
								this_thread::sleep_for(chrono::milliseconds(1));
							}
							
							m.lock();
							cout << "......Export items......\t" << el.GetvehicleName() << endl;
							a -= el.GetvehicleCapacity();
							cout << "Items in Warehouse: " << a << endl;
							m.unlock();
						}
						/*m.lock();
						cout << "Wait" << endl;
						this_thread::sleep_for(chrono::milliseconds(1000));
						m.unlock();*/
						
					}
				}));
		}
		
		while (a + f.GetfactoryItemPerHour() > w.GetwarehouseCapacity())
		{
			this_thread::sleep_for(chrono::milliseconds(1));
		}
		this_thread::sleep_for(chrono::milliseconds(1000));
		cout << "......Import items......" << endl;
		a += f.GetfactoryItemPerHour();
		cout << "Items in Warehouse: " << a << endl;

		
		
	}
	t1.detach();
}
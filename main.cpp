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

void foo(Warehouse &w, vector<Factory>&f, vector<Vehicle> &v);
int a = 0;
mutex m;

int main()
{
	Warehouse w(3000);
	Product p("Milk", 1000, "Cartoon");
	Factory f("a", p, 150), f2("b", p, 200), f3("c", p, 350);
	vector<Vehicle> vv = { Vehicle ("Gazel", 270), Vehicle("Kamaz", 500) };
	vector<Factory> vf = { Factory("a", p, 150), Factory("b", p, 200), Factory("c", p, 350) };

	foo(w, vf, vv);

	
	return 0;
}

void foo(Warehouse &w, vector<Factory> &f, vector<Vehicle> &v)
{
	
	thread *t = new thread [f.size()];
	while (true)
	{
		
		for (auto el = 0; el < f.size(); el++)
		{
			if (a >= w.GetwarehouseCapacity() * 95 / 100 || a + f[el].GetfactoryItemPerHour() > w.GetwarehouseCapacity())
			{
				if (t[el].joinable() == true) //Защита от повторного вызова существующего потока
				{
					cout << "Potok closed" << endl;
					t[el].detach();
				}

				cout << "Potok open" << endl;
				t[el] = (thread([&]()
					{
						while (a >= 0)
						{
							for (auto& elv : v)
							{
								while (f[el].factoryCapacity - elv.GetvehicleCapacity() < 0)
								{
									this_thread::sleep_for(chrono::milliseconds(1));
									
								}

								m.lock();
								cout << "......Export items......\t" << elv.GetvehicleName() << "\tFactory: " << f[el].GetfactoryName() << endl;
								f[el].factoryCapacity -= elv.GetvehicleCapacity();
								a -= elv.GetvehicleCapacity();
								cout << "Items in Warehouse: " << a << "\t\tItems in Factory: " << f[el].factoryCapacity << endl;
								m.unlock();
							}
							

						}
					}));
			}

			while (a + f[el].GetfactoryItemPerHour() > w.GetwarehouseCapacity())
			{
				this_thread::sleep_for(chrono::milliseconds(1));
				
				
			}
			this_thread::sleep_for(chrono::milliseconds(3000));
			cout << "......Import items......\tFactory: " << f[el].GetfactoryName() << endl;
			a += f[el].GetfactoryItemPerHour();
			f[el].factoryCapacity += f[el].GetfactoryItemPerHour();
			cout << "Items in Warehouse: " << a << "\t\tItems in Factory: " << f[el].factoryCapacity << endl;
			



		}
	}
	t[0].detach();
	t[1].detach();
	t[2].detach();
	delete[] t;
}
#include <iostream>
#include <math.h>
#include <vector>
#include <cstdlib>
#include <cmath>
#include <fstream>
#include <string>
class BaseClass
{
private:
	std::string name ;//��� �����
	int n0;//x ���������� ������
	int m0;//� ���������� ������
	double d;//������� ��� ����� �����
	int r;//����������� � ������� ������� ������
	double doubleRad;//������
	double lK;//������ ��� ������ n
	double rK;//������ ��� ������� n
	int lN;//����� n (x ����������)
	int rN;//������ n 
	double deltaLeftK;//������� ��� ������ "�������"
	double deltaRightK;//������ ��� ������� "�������"
	int m;//��������� �������� �� ��� 'y'
	bool detectFig = false;//True ��� ���������� ��������, ������������ � ������ ���������
	int x;
	int y;
	bool begin = false;//���� ��� ������ ��������� ����������
	int beginX;
	int beginY;
	int endX;
	int endY;

	std::vector <std::vector<int>> readArr;//������ ��� ������ �� �����
	std::vector <std::vector<int>> imArr;//������ ��� �������� "����������"
	//Circle(int n0, int m0, int d)

public:
	BaseClass(std::string inputName)
	{
		this->name = inputName;
		fillArray();//���������� �������
		readArray();
	}
	~BaseClass(){}

	void readArray()//������ ������� �� ����� � ������ ��� � readArr
	{
		std::ifstream fin;
		fin.open(name);

		if (!fin.is_open())
		{
			std::cout << " invalid name" << std::endl;
		}
		else
		{
			char ch;
			int buffI;
			for (int i = 0; i < 15; i++)
			{

				for (int j = 0; j < 15; )
				{
					fin.get(ch);
					buffI = ch;
					if (buffI == 48)
					{
						readArr[i][j] = 0;
						j++;
					}
					if (buffI == 49)
					{
						readArr[i][j] = 1;
						j++;
					}
				}

			}
		}
		for (int i = 0; i < 15; i++)
		{
			for (int j = 0; j < 15; j++)
			{
				std::cout << readArr[i][j];
			}
			std::cout << std::endl;
		}

		findSign();
	}
	void findSign()//���������� ��������� � �������� ���������� ������, ����� ���������� � ��������� "���������" ��������� ����� � �������� ����� ��������� �������� ������ ��� ������������ ���������
	{
		for (int i = 0; i < 15; i++)//����� � ������ ��������� ����������
		{
			for (int j = 0; j < 15; j++)
			{
				if (readArr[i][j] == 1)
				{
					beginX = j;
					beginY = i;
					begin = true;
					break;
					
				}
				
			}
			if (begin != false)
			{
				break;
			}
		}
		for (int i = 0; i < 15; i++)//����� � ������ �������� ����������
		{
			for (int j = 0; j < 15; j++)
			{
				if (readArr[i][j] != 0)
				{
					endX = j;
					endY = i;
				}
			}
		}
		if (endX - beginX> 2)
		{
			createRectangle();//��������� �������� ��� ��������� � ������� imArr
			comparison();//���������, ���� �� �����, �� ���������� detectFig = true
			if (detectFig != true)
			{
				std::cout << " Rectangle, lenght = " << endX-beginX  + 1 << std::endl;
				std::cout << " x: " << beginX << " y:" << beginY << std::endl;
			}
			else
			{
				std::cout << " Unknown figure" << std::endl;
			}
		}
		if (endX - beginX < 3)//������� ��� ����������
		{
			x = (endX + beginX) / 2;//x ���������� ������
			y = (endY + beginY) / 2;//y ���������� ������

			createCircle(x, y, endY - beginY + 1);
			comparison();//���������, ���� �� �����, �� ���������� detectFig = true
			if (detectFig != true)
			{
				std::cout << " Circle, diameter = " << endY - beginY + 1 << std::endl;
				std::cout << " x: " << x <<" y:"<<y<< std::endl;
			}
			else
			{
				std::cout << " Unknown figure" << std::endl;
			}
		}
	}

	void comparison()//��������� ����������� ������ � ������������ 
	{
		for (int i = 0; i < 15; i++)//����� � ������ �������� ����������
		{
			for (int j = 0; j < 15; j++)
			{
				if (readArr[i][j] != imArr[i][j])
				{
					detectFig = true;
					break;
				}
			}
			if (detectFig != false)
			{
				break;
			}
		}
	}

	void fillArray()//��������� ������ ������
	{

		for (int i = 0; i < 15; i++)
		{
			std::vector <int> temp;

			for (int j = 0; j < 15; j++)
			{
				temp.push_back(0);
			}
			readArr.push_back(temp);
			imArr.push_back(temp);
		}
	}
	//�������� �������������� 
	void createRectangle()
	{
		d = endX - beginX + 1;
		for (int i = 0; i < d; i++)
		{
			for (int j = 0; j < d; j++)
			{
				imArr[beginY + i][beginX + j] = 1;
			}
		}
	}

	//�������� ����������
	void createCross()//��������������� ����� ��� �������� ����������, ������� ����� - ������ ��� �����
	{
		for (int i = 0; i < d; i++)
		{
			imArr[n0 - r + i][m0] = 1;
			imArr[n0][m0 - r + i] = 1;
		}
	}

	void copyPath()//��������������� ����� ��� �������� ���������� �������� ������ �������� ����� � ��������� ��������
	{
		for (int i = 1; i != r + 1; i++)
		{
			for (int j = 1; j != r + 1; j++)
			{
				imArr[m0 - j][n0 + i] = imArr[m0 - j][n0 - i];//  2/4
				imArr[m0 + j][n0 + i] = imArr[m0 - j][n0 - i];//  3/4
				imArr[m0 + j][n0 - i] = imArr[m0 - j][n0 - i];//  4/4
			}
		}
	}

	void createCircle(int n0, int m0, int d)//������ ���� �� "��������" 
	{
		this->n0 = n0;
		this->m0 = m0;
		this->d = d;
		r = d / 2;
		doubleRad = r + 0.5;
		lN = n0 - r;
		rN = lN + 1;
		m = m0;
		createCross();

		for (int i = 0; i < r; i++)
		{

			m = m - 1;

			lK = sqrt((n0 - lN + 0.5)*(n0 - lN + 0.5) + (m0 - m + 0.5)*(m0 - m + 0.5));//"������" ��� ����� ����������
			rK = sqrt((n0 - rN + 0.5)*(n0 - rN + 0.5) + (m0 - m + 0.5)*(m0 - m + 0.5));//����� lN ������, ����� ��� ��������� � ������ ������ ��� ����������

			deltaLeftK = abs(lK - doubleRad);//������ �� �������� �������� ��� left
			deltaRightK = abs(rK - doubleRad);//������ �� �������� �������� ��� right

			if (deltaLeftK > deltaRightK)//���������� '1' ���������� � "��������", �������� �������� �� ������� ����������
			{
				imArr[m][rN] = 1;
				lN = rN;//������� ����������� �� x ���������� "������ �����" (��� ��������� ��������)
				if (r > 2)
				{
					for (int i = rN + 1; i != n0; i++)
					{
						imArr[m][i] = 1;
					}
				}
			}
			else
			{
				imArr[m][lN] = 1;
				if (r > 2)
				{
					for (int i = lN + 1; i != n0; i++)
					{
						imArr[m][i] = 1;
					}
				}
			}
			rN = lN + 1;
		}
		copyPath();
	}

	void showArr()
	{
		for (int i = 0; i < 15; i++)
		{
			for (int j = 0; j < 15; j++)
			{
				std::cout << imArr[i][j];
			}
			std::cout << std::endl;
		}
	}
};
int main() {

	std::string name;
	std::cout << "Input file name:" << "\n";
	std::getline(std::cin,name);
	BaseClass a(name);
	std::cout << "\n";

	system("pause");
	return 0;
}
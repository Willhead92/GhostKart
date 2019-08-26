#pragma once
#include <cmath>
class Vector2D
{
public:
	//atributos
	float x;
	float y;

	//métodos
	Vector2D(float xi = 0.0f, float yi = 0.0f) : x(xi), y(yi) {};
	virtual~Vector2D();
	void setPos(float xi, float yi)						{ x = xi, y = yi; }
	float  modulo()										{ return (float)sqrt(x * x + y * y);	}
	float argumento()									{ return (float)atan2(y, x);			}
	Vector2D operator - (Vector2D &v)					{ return Vector2D(x - v.x, y - v.y);	}
	Vector2D operator + (Vector2D &v)					{ return Vector2D(x + v.x, y + v.y);	}
	float operator *(Vector2D &v)						{ return x * v.x + y * v.y;				}//producto escalar
	Vector2D operator *(float n)						{ return Vector2D(x*n, y*n);			} //producto por un escalar
	Vector2D unitario();
};
//las funciones-operador son buenas candidatas para ser declaradas funciones inline

//pasamos por referencia el argumento ya que, aunque la variable no es modificada,
//es más eficiente, pasar por referencia es más rápido que por valor
//combiene hacer esto cuando es grande la información contenida dentro del objeto
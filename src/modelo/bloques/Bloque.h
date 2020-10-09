#ifndef SRC_MODELO_BLOQUES_BLOQUE_H_
#define SRC_MODELO_BLOQUES_BLOQUE_H_


class Bloque{
    public:

		virtual ~Bloque(){};

    protected:


};

class Sorpresa : public Bloque{
    public:
		Sorpresa(){
		}

        ~Sorpresa(){
        }

};


#endif /* SRC_MODELO_BLOQUES_BLOQUE_H_ */

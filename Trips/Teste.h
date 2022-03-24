#ifndef TESTE_H_
#define TESTE_H_

#include <assert.h>
#include <exception>
#include "Utils.h"
#include "Oferta.h"
#include "Repository.h"
#include "Service.h"
#include "Exceptions.h"

class Teste
{
public:

	void teste_all() const;

private:

	void teste_utils() const;
	void teste_domain() const;
	void teste_RepositoryOferta() const;
	void teste_RepositoryLab() const;
	void teste_RepositoryLabFailure() const;
	void teste_service() const;
	void teste_service_files() const;
	void teste_service_lab() const;
	void teste_undo() const;
	
};

#endif

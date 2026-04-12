// vector<Jornada> jornadas;
auto it = std::find_if(jornadas.begin(), jornadas.end(),
    [numeroSeleccionado, idLligaSeleccionada](const Jornada& j) {
        return j.getNumero() == numeroSeleccionado && j.getLligaId() == idLligaSeleccionada;
    });
if (it == jornadas.end()) { /* manejar error */ }
int idJornada = it->getId();
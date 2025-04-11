package pt.estgp.es.spring.dao;


import org.springframework.data.repository.CrudRepository;
import pt.estgp.es.spring.domain.Classes;

public interface ClassesRepository extends CrudRepository<Classes, Integer> {
}
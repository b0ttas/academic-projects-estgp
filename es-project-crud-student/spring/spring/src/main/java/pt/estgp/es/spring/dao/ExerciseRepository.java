package pt.estgp.es.spring.dao;


import org.springframework.data.repository.CrudRepository;
import pt.estgp.es.spring.domain.Exercise;

public interface ExerciseRepository extends CrudRepository<Exercise, Integer> {
}
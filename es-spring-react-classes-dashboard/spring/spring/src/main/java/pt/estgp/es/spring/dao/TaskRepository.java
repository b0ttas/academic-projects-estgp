package pt.estgp.es.spring.dao;


import org.springframework.data.repository.CrudRepository;
import pt.estgp.es.spring.domain.Task;

public interface TaskRepository extends CrudRepository<Task, Integer> {
}
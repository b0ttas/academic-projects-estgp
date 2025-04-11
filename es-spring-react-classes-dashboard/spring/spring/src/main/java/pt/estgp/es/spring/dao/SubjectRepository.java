package pt.estgp.es.spring.dao;


import org.springframework.data.repository.CrudRepository;
import pt.estgp.es.spring.domain.Subject;

public interface SubjectRepository extends CrudRepository<Subject, Integer> {
}
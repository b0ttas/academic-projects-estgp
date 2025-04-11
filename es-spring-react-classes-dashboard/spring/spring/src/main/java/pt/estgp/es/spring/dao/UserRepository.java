package pt.estgp.es.spring.dao;


import org.springframework.data.jpa.repository.Query;
import org.springframework.data.repository.CrudRepository;
import org.springframework.data.repository.query.Param;
import org.springframework.stereotype.Repository;
import pt.estgp.es.spring.domain.User;

import java.util.List;

@Repository
public interface UserRepository extends CrudRepository<User, Integer> {
    @Query("SELECT u FROM User u WHERE u.email = ?1")
    User findByEmail(String emailAddress);

    @Query("SELECT u FROM User u WHERE u.username = ?1")
    User findByUsername(String username);

    @Query("SELECT u FROM User u JOIN u.subjects s WHERE s.id = :subjectId and u.role.id = 1")
    List<User> findBySubjectId(@Param("subjectId") Integer subjectId);
}

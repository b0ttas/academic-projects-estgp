package pt.estgp.es.spring.dao;

import org.springframework.data.repository.CrudRepository;
import pt.estgp.es.spring.domain.Role;

public interface RoleRepository extends CrudRepository<Role, Integer> {
}

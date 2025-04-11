package pt.estgp.es.spring.services;

import lombok.AllArgsConstructor;
import org.springframework.stereotype.Service;
import pt.estgp.es.spring.dao.TaskRepository;
import pt.estgp.es.spring.dao.UserRepository;
import pt.estgp.es.spring.domain.Task;
import pt.estgp.es.spring.domain.User;

import java.util.Optional;

@Service
@AllArgsConstructor
public class TaskService {
    private final TaskRepository taskRepository;
    private final UserRepository userRepository;

    //@Transactional
    public Iterable<Task> getUserTasks(Integer userId) {
        User user = userRepository.findById(userId).orElse(null);
        assert user != null;
        return user.getTasks();
    }

    public Optional<Task> getTask(Integer id) {
        return taskRepository.findById(id);
    }
}
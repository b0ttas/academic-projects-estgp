package pt.estgp.es.spring.services;

import lombok.AllArgsConstructor;
import org.springframework.data.repository.query.Param;
import org.springframework.security.access.prepost.PreAuthorize;
import org.springframework.stereotype.Service;
import org.springframework.transaction.annotation.Transactional;
import pt.estgp.es.spring.dao.*;
import pt.estgp.es.spring.domain.*;
import pt.estgp.es.spring.services.exceptions.EntityNotFoundException;

import java.util.*;

@Service
@AllArgsConstructor
public class UserService {
    private final UserRepository userRepository;
    private final UserClassPerformanceRepository userClassPerformanceRepository;
    private final SubjectRepository subjectRepository;
    private final ClassesRepository classesRepository;
    private final ExerciseRepository exerciseRepository;
    private final TaskRepository taskRepository;

    @Transactional
    @PreAuthorize("hasRole('ROLE_ADMIN')")
    public void saveUser(@Param("view") User view) throws EntityNotFoundException {
        Optional<User> byId = userRepository.findById(view.getId());
        if (byId.isEmpty()) {
            throw new EntityNotFoundException();
        }
        User student = byId.get();
        student.setFirstName(view.getFirstName());
        userRepository.save(student);
    }

    @Transactional
    public User load(Integer id) throws EntityNotFoundException {
        Optional<User> byId = userRepository.findById(id);
        if (byId.isEmpty()) {
            throw new EntityNotFoundException();
        }
        return byId.get();
    }

    @Transactional
    public User newUser(User user) {
        return userRepository.save(user);
    }

    @Transactional
    public void addSubjectToUser(Integer userId, Integer subjectId) {
        User user = userRepository.findById(userId).orElseThrow(() -> new RuntimeException("User not found"));
        Subject subject = subjectRepository.findById(subjectId).orElseThrow(() -> new RuntimeException("Subject not found"));

        user.getSubjects().add(subject);

        userRepository.save(user);
    }

    @Transactional
    public void addClassToUser(Integer userId, Integer classId) {
        User user = userRepository.findById(userId).orElseThrow(() -> new RuntimeException("User not found"));
        Classes classes = classesRepository.findById(classId).orElseThrow(() -> new RuntimeException("Class not found"));

        UserClassPerformance performance = new UserClassPerformance();
        performance.setUser(user);
        performance.setClasses(classes);
        // Set initial performance metrics here, if any

        userClassPerformanceRepository.save(performance);
    }

    @Transactional
    public void addExerciseToUser(Integer userId, Integer exerciseId) {
        User user = userRepository.findById(userId).orElseThrow(() -> new RuntimeException("User not found"));
        Exercise exercise = exerciseRepository.findById(exerciseId).orElseThrow(() -> new RuntimeException("Exercise not found"));

        user.getExercises().add(exercise);

        userRepository.save(user);
    }

    @Transactional
    public void addTaskToUser(Integer userId, Integer taskId) {
        User user = userRepository.findById(userId).orElseThrow(() -> new RuntimeException("User not found"));
        Task task = taskRepository.findById(taskId).orElseThrow(() -> new RuntimeException("Task not found"));

        user.getTasks().add(task);

        userRepository.save(user);
    }

    public Map<String, Set<Subject>> getAllUsersAndTheirSubjects() {
        List<User> users = (List<User>) userRepository.findAll();
        Map<String, Set<Subject>> userSubjects = new HashMap<>();

        for (User user : users) {
            userSubjects.put(user.getUsername(), user.getSubjects());
        }

        return userSubjects;
    }
}

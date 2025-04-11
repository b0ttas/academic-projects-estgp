package pt.estgp.es.spring.controllers;

import lombok.AllArgsConstructor;
import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.security.access.prepost.PreAuthorize;
import org.springframework.security.crypto.bcrypt.BCryptPasswordEncoder;
import org.springframework.web.bind.annotation.*;
import pt.estgp.es.spring.dao.UserRepository;
import pt.estgp.es.spring.domain.*;
import pt.estgp.es.spring.services.ClassesService;
import pt.estgp.es.spring.services.ExerciseService;
import pt.estgp.es.spring.services.SubjectService;
import pt.estgp.es.spring.services.TaskService;

import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.Optional;

@RestController
@AllArgsConstructor
public class UserController {
    private final SubjectService subjectsService;
    private final ClassesService classesService;
    private final ExerciseService exerciseService;
    private final TaskService taskService;
    private final UserRepository userRepository;

    @GetMapping(path = "/api/users")
    @PreAuthorize("hasRole('ROLE_ADMIN')")
    public @ResponseBody List<User> getUsers() {
        return (List<User>) userRepository.findAll();
    }

    //@PreAuthorize("hasAnyRole('ROLE_ADMIN', 'ROLE_TEACHER')")
    @GetMapping(path = "/api/users/{id}")
    public @ResponseBody Optional<User> getUserById(@PathVariable Integer id) {
        return userRepository.findById(id);
    }

    //    @GetMapping(path = "/api/users/{id}")
    //    @PreAuthorize("hasRole('STUDENT')")
    //    public @ResponseBody Optional<User> getOwnUserById(@PathVariable Integer id, Principal principal) {
    //        User currentUser = userRepository.findByUsername(principal.getName());
    //        if (currentUser.getId().equals(id)) {
    //            return userRepository.findById(id);
    //        } else {
    //            throw new ResponseStatusException(HttpStatus.FORBIDDEN, "You are not allowed to access other users' data");
    //        }
    //    }
    @PreAuthorize("hasRole('ROLE_ADMIN')")
    @DeleteMapping(path = "/api/users/{id}")
    public @ResponseBody ResponseEntity<Object> deleteUserById(@PathVariable Integer id) {
        Map<String, String> response = new HashMap<>();
        try {
            userRepository.deleteById(id);
            response.put("message", "User with ID " + id + " deleted successfully.");
            return new ResponseEntity<>(response, HttpStatus.OK);
        } catch (Exception e) {
            response.put("message", "Error deleting user with ID " + id);
            return new ResponseEntity<>(response, HttpStatus.BAD_REQUEST);
        }
    }

    @PreAuthorize("hasRole('ROLE_ADMIN')")
    @PostMapping(path = "/api/users")
    public @ResponseBody ResponseEntity<Object> createUserOrUpdate(@RequestBody User user) {
        Map<String, String> response = new HashMap<>();
        try {
            String hashedPassword = new BCryptPasswordEncoder().encode(user.getPassword());
            user.setPassword(hashedPassword);

            User savedUser = userRepository.save(user);
            response.put("message", "User with ID " + savedUser.getId() + " created or updated successfully.");
            return new ResponseEntity<>(response, HttpStatus.OK);
        } catch (Exception e) {
            response.put("message", "Error creating or updating user");
            return new ResponseEntity<>(response, HttpStatus.BAD_REQUEST);
        }
    }

    @GetMapping(path = "/api/users/{id}/subjects")
    public @ResponseBody Iterable<Subject> getSubjectByUserId(@PathVariable Integer id) {
        return subjectsService.getUserSubjects(id);
    }

    @GetMapping(path = "/api/users/{id}/classes")
    public @ResponseBody Iterable<Classes> getClassesByUserId(@PathVariable Integer id) {
        return classesService.getUserClasses(id);
    }

    @GetMapping(path = "/api/users/{id}/exercises")
    public @ResponseBody Iterable<Exercise> getExerciseByUserId(@PathVariable Integer id) {
        return exerciseService.getUserExercises(id);
    }

    @GetMapping(path = "/api/users/{id}/tasks")
    public @ResponseBody Iterable<Task> getTaskByUserId(@PathVariable Integer id) {
        return taskService.getUserTasks(id);
    }
}
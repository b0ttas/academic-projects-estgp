package pt.estgp.es.spring.controllers;

import lombok.AllArgsConstructor;
import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.security.access.prepost.PreAuthorize;
import org.springframework.web.bind.annotation.*;
import pt.estgp.es.spring.dao.SubjectRepository;
import pt.estgp.es.spring.domain.Classes;
import pt.estgp.es.spring.domain.Subject;
import pt.estgp.es.spring.domain.User;
import pt.estgp.es.spring.services.ClassesService;
import pt.estgp.es.spring.services.SubjectService;

import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.Optional;

@RestController
@AllArgsConstructor
public class ClassesController {
    private final SubjectRepository subjectRepository;
    private final ClassesService classesService;
    private final SubjectService subjectService;

    @GetMapping(path = "/api/classes")
    public @ResponseBody List<Subject> getClasses() {
        return (List<Subject>) subjectRepository.findAll();
    }

    @GetMapping(path = "/api/subjects/{id}/classes")
    public @ResponseBody Iterable<Classes> getSubjectClasses(@PathVariable Integer id) {
        return classesService.getSubjectClasses(id);
    }

    @PreAuthorize("hasRole('ROLE_ADMIN')")
    @DeleteMapping(path = "/api/classes/{id}")
    public @ResponseBody ResponseEntity<Object> deleteClassesById(@PathVariable Integer id) {
        Map<String, String> response = new HashMap<>();
        try {
            classesService.deleteById(id);
            response.put("message", "Class with ID " + id + " deleted successfully.");
            return new ResponseEntity<>(response, HttpStatus.OK);
        } catch (Exception e) {
            response.put("message", "Error deleting class with ID " + id);
            return new ResponseEntity<>(response, HttpStatus.BAD_REQUEST);
        }
    }

    @PostMapping(path = "/api/subjects/{id}/classes")
    public ResponseEntity<?> createClass(@PathVariable Integer id, @RequestBody Classes newClass) {
        Map<String, String> response = new HashMap<>();
        Optional<Subject> subjectOptional = subjectRepository.findById(id);
        if (subjectOptional.isEmpty()) {
            return new ResponseEntity<>(HttpStatus.NOT_FOUND);
        } else {
            Subject subject = subjectOptional.get();

            newClass.setSubject(subject);
            Classes savedClass = classesService.save(newClass);

            response.put("message", savedClass.toString());
            return new ResponseEntity<>(response, HttpStatus.CREATED);
        }
    }

    //@Transactional
    @PostMapping(path = "/api/subjects/{id}/users")
    public ResponseEntity<?> postUsersBySubject(@RequestBody Iterable<User> users, @PathVariable String id) {
        Map<String, String> response = new HashMap<>();
        try {
            classesService.postUsersBySubject(users);
            response.put("message", "Users updated successfully");
            return new ResponseEntity<>(response, HttpStatus.OK);
        } catch (Exception e) {
            response.put("message", "An error occurred while adding users");
            return new ResponseEntity<>(response, HttpStatus.INTERNAL_SERVER_ERROR);
        }
    }

    @PreAuthorize("hasRole('ROLE_ADMIN')")
    @PostMapping(path = "/api/classes")
    public @ResponseBody ResponseEntity<Object> createClassOrUpdate(@RequestBody Classes classes) {
        Map<String, String> response = new HashMap<>();
        try {
            Classes savedClass = classesService.save(classes);
            response.put("message", "Class with ID " + savedClass.getId() + " created or updated successfully.");
            return new ResponseEntity<>(response, HttpStatus.OK);
        } catch (Exception e) {
            response.put("message", "Error creating or updating class");
            return new ResponseEntity<>(response, HttpStatus.BAD_REQUEST);
        }
    }

}
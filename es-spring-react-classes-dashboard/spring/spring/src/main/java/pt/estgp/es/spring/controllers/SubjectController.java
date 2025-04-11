package pt.estgp.es.spring.controllers;

import lombok.AllArgsConstructor;
import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.security.access.prepost.PreAuthorize;
import org.springframework.web.bind.annotation.*;
import pt.estgp.es.spring.domain.Subject;
import pt.estgp.es.spring.domain.User;
import pt.estgp.es.spring.services.SubjectService;

import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.Optional;

@RestController
@AllArgsConstructor
public class SubjectController {
    private final SubjectService subjectsService;

    @GetMapping(path = "/api/subjects")
    @PreAuthorize("hasRole('ROLE_ADMIN')")
    public @ResponseBody List<Subject> getSubjects() {
        return (List<Subject>) subjectsService.findAll();
    }

    @GetMapping(path = "/api/subjects/{id}")
    public @ResponseBody Optional<Subject> getSubject(@PathVariable Integer id) {
        return subjectsService.getSubject(id);
    }

    @GetMapping(path = "/api/subjects/{id}/users")
    public @ResponseBody Iterable<User> getUsersBySubject(@PathVariable Integer id) {
        return subjectsService.getUsersBySubject(id);
    }

    @PreAuthorize("hasRole('ROLE_ADMIN')")
    @DeleteMapping(path = "/api/subjects/{id}")
    public @ResponseBody ResponseEntity<Object> deleteSubjectsById(@PathVariable Integer id) {
        Map<String, String> response = new HashMap<>();
        try {
            subjectsService.deleteById(id);
            response.put("message", "Class with ID " + id + " deleted successfully.");
            return new ResponseEntity<>(response, HttpStatus.OK);
        } catch (Exception e) {
            response.put("message", "Error deleting class with ID " + id);
            return new ResponseEntity<>(response, HttpStatus.BAD_REQUEST);
        }
    }

    @PreAuthorize("hasRole('ROLE_ADMIN')")
    @PostMapping(path = "/api/subjects")
    public @ResponseBody ResponseEntity<Object> createSubjectOrUpdate(@RequestBody Subject subject) {
        Map<String, String> response = new HashMap<>();
        try {
            Subject savedSubject = subjectsService.save(subject);
            response.put("message", "Subject with ID " + savedSubject.getId() + " created or updated successfully.");
            return new ResponseEntity<>(response, HttpStatus.OK);
        } catch (Exception e) {
            response.put("message", "Error creating or updating subject");
            return new ResponseEntity<>(response, HttpStatus.BAD_REQUEST);
        }
    }

}
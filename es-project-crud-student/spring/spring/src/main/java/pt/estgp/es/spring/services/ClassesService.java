package pt.estgp.es.spring.services;

import javassist.NotFoundException;
import lombok.AllArgsConstructor;
import org.springframework.stereotype.Service;
import pt.estgp.es.spring.dao.ClassesRepository;
import pt.estgp.es.spring.dao.SubjectRepository;
import pt.estgp.es.spring.dao.UserClassPerformanceRepository;
import pt.estgp.es.spring.dao.UserRepository;
import pt.estgp.es.spring.domain.Classes;
import pt.estgp.es.spring.domain.Subject;
import pt.estgp.es.spring.domain.User;
import pt.estgp.es.spring.domain.UserClassPerformance;

import java.util.Optional;
import java.util.stream.Collectors;

@Service
@AllArgsConstructor
public class ClassesService {
    private final ClassesRepository classesRepository;
    private final UserRepository userRepository;
    private final UserClassPerformanceRepository userClassPerformanceRepository;
    private final SubjectRepository subjectRepository;

    public Iterable<Classes> getUserClasses(Integer userId) {
        User user = userRepository.findById(userId).orElse(null);
        assert user != null;
        return user.getPerformances().stream()
                .map(UserClassPerformance::getClasses)
                .collect(Collectors.toList());
    }

    public Optional<Classes> getClass(Integer id) {
        return classesRepository.findById(id);
    }

    public Iterable<Classes> getSubjectClasses(Integer id) {
        Subject subject = subjectRepository.findById(id).orElse(null);
        assert subject != null;
        return subject.getClasses();
    }

    public void postUsersBySubject(Iterable<User> users) throws NotFoundException {
        for (User user : users) {
            userRepository.findById(user.getId()).orElseThrow(() -> new NotFoundException("User not found"));
            userClassPerformanceRepository.saveAll(user.getPerformances());
        }
    }

    public Classes save(Classes newClass) {
        return classesRepository.save(newClass);
    }

    public void deleteById(Integer id) {
        classesRepository.deleteById(id);
    }
}
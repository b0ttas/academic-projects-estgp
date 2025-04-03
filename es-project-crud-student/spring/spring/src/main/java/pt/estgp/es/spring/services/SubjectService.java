package pt.estgp.es.spring.services;

import lombok.AllArgsConstructor;
import org.springframework.stereotype.Service;
import pt.estgp.es.spring.dao.SubjectRepository;
import pt.estgp.es.spring.dao.UserClassPerformanceRepository;
import pt.estgp.es.spring.dao.UserRepository;
import pt.estgp.es.spring.domain.Subject;
import pt.estgp.es.spring.domain.User;

import java.util.Optional;

@Service
@AllArgsConstructor
public class SubjectService {
    private final SubjectRepository subjectRepository;
    private final UserRepository userRepository;
    private final UserClassPerformanceRepository userClassPerformanceRepository;

    //@Transactional
    public Iterable<Subject> getUserSubjects(Integer userId) {
        User user = userRepository.findById(userId).orElse(null);
        assert user != null;
        return user.getSubjects();
    }

    public Optional<Subject> getSubject(Integer id) {
        return subjectRepository.findById(id);
    }

    public Iterable<Subject> findAll() {
        return subjectRepository.findAll();
    }

    public Iterable<User> getUsersBySubject(Integer subject_id) {
        return userRepository.findBySubjectId(subject_id);
    }

    public void deleteById(Integer id) {
        subjectRepository.deleteById(id);
    }

    public Subject save(Subject subject) {
        return subjectRepository.save(subject);
    }
}
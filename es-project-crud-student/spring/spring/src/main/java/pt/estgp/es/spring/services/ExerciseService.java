package pt.estgp.es.spring.services;

import lombok.AllArgsConstructor;
import org.springframework.stereotype.Service;
import pt.estgp.es.spring.dao.ExerciseRepository;
import pt.estgp.es.spring.dao.UserRepository;
import pt.estgp.es.spring.domain.Exercise;
import pt.estgp.es.spring.domain.User;

import java.util.Optional;

@Service
@AllArgsConstructor
public class ExerciseService {
    private final ExerciseRepository exerciseRepository;
    private final UserRepository userRepository;

    //@Transactional
    public Iterable<Exercise> getUserExercises(Integer userId) {
        User user = userRepository.findById(userId).orElse(null);
        assert user != null;
        return user.getExercises();
    }

    public Optional<Exercise> getExercise(Integer id) {
        return exerciseRepository.findById(id);
    }
}
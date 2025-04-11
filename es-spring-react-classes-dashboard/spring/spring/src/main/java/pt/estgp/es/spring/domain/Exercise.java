package pt.estgp.es.spring.domain;

import jakarta.persistence.*;
import lombok.Getter;
import lombok.Setter;

import java.util.Set;

@Setter
@Getter
@Entity
public class Exercise {
    @Id
    @GeneratedValue(strategy = GenerationType.AUTO)
    private Integer id;
    @ManyToOne
    @JoinColumn(name = "subject_id")
    private Subject subject;
    @ManyToOne
    @JoinColumn(name = "class_id")
    private Classes class_id;
    @ManyToOne
    @JoinColumn(name = "student_id")
    private User student;
    private String description;
    private String title;
    @OneToMany(mappedBy = "exercise")
    private Set<Task> tasks;
}
package pt.estgp.es.spring.domain;

import com.fasterxml.jackson.annotation.JsonBackReference;
import com.fasterxml.jackson.annotation.JsonIgnore;
import jakarta.persistence.*;
import lombok.Getter;
import lombok.Setter;
import org.hibernate.annotations.Cascade;
import org.hibernate.annotations.CascadeType;

import java.util.Date;
import java.util.Set;

@Setter
@Getter
@Entity
public class Classes {
    @Id
    @GeneratedValue(strategy = GenerationType.AUTO)
    private Integer id;

    @OneToMany(mappedBy = "classes")
    @JsonIgnore
    @Cascade(CascadeType.REMOVE)
    private Set<UserClassPerformance> performances;

    @ManyToOne
    @JoinColumn(name = "subject_id")
    @JsonBackReference
    private Subject subject;

    @OneToMany(mappedBy = "class_id")
    private Set<Exercise> exercises;
    private Date date;
}
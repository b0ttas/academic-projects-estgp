package pt.estgp.es.spring.domain;

import com.fasterxml.jackson.annotation.JsonIgnore;
import jakarta.persistence.*;
import lombok.Getter;
import lombok.Setter;

@Entity
@Setter
@Getter
//@IdClass(UserClassPerformanceId.class)
public class UserClassPerformance {
    @Id
    @GeneratedValue(strategy = GenerationType.AUTO)
    private int id;
    private int user_id;
    //@ManyToOne
    //@JoinColumn(name = "user_id")
    //@JsonBackReference(value = "user-performance")
    //@JsonIdentityReference(alwaysAsId = true)

    private int classes_id;
    //@ManyToOne
    //@JoinColumn(name = "class_id")
    //@JsonBackReference(value = "class-performance")
    //@JsonIdentityReference(alwaysAsId = true)

    private Double interpretation;
    private Double autonomy;
    private Double interventions;

    @JsonIgnore
    @ManyToOne
    @JoinColumn(name = "user_id", referencedColumnName = "ID", insertable = false, updatable = false)
    private User user;
    @JsonIgnore
    @ManyToOne
    @JoinColumn(name = "classes_id", referencedColumnName = "ID", insertable = false, updatable = false)
    private Classes classes;

}


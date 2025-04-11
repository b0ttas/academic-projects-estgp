package pt.estgp.es.spring.domain;

import lombok.Getter;
import lombok.Setter;

import java.io.Serializable;

@Getter
@Setter
public class UserClassPerformanceId implements Serializable {
    private int user_id;
    private int classes_id;
}
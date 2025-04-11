package pt.estgp.es.spring;

import org.junit.jupiter.api.Test;

import static org.assertj.core.api.Assertions.assertThat;

public class UnityTest {
    @Test
    public void testFirstLastName()
    {
        boolean dummyTest = 2 > 1;
        System.out.println("Running UnityTest");
        assertThat(dummyTest).isEqualTo(true);
    }

}

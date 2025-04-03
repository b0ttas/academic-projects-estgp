package pt.estgp.es.spring;


import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.beans.factory.annotation.Value;
import org.springframework.boot.test.context.SpringBootTest;
import org.springframework.boot.test.context.SpringBootTest.WebEnvironment;
import org.springframework.boot.test.web.client.TestRestTemplate;
import pt.estgp.es.spring.utils.JwtTokenUtil;

@SpringBootTest(webEnvironment = WebEnvironment.RANDOM_PORT)
public class HttpRequestTest {

    @Autowired
    JwtTokenUtil jwtTokenUtil;
    @Value(value = "${local.server.port}")
    private int port;
    //TODO: see below
    //    @Test
    //    public void greetingShouldReturnDefaultMessage() throws Exception {
    //        assertThat(this.restTemplate.getForObject("http://localhost:" + port + "/api/v1/hello",
    //                String.class)).contains("Hello world");
    //    }
    @Autowired
    private TestRestTemplate restTemplate;
    // TODO: Re-enable after fix
    //    @Test
    //    public void testAuthentication() throws Exception
    //    {
    //        JwtRequest jwtRequest = new JwtRequest("j@1","123");
    //        ResponseEntity<String> responseEntityStr  = restTemplate.postForEntity("http://localhost:" + port + "/authenticate",
    //                jwtRequest, String.class);
    //        assertThat(responseEntityStr.getStatusCode().value()).isEqualTo(HttpStatus.OK.value());
    //        System.out.println(responseEntityStr.getBody());
    //        String token = new JSONObject(responseEntityStr.getBody()).getString("token");
    //        String usernameFromToken = jwtTokenUtil.getUsernameFromToken(token);
    //        assertThat(usernameFromToken).isEqualTo("j@1");
    //
    //
    //
    //        ResponseEntity<User> responseAlunoEntity =
    //                restTemplate.getForEntity("http://localhost:" + port + "/api/v1/alunos/1",User.class);
    //        assertThat(responseAlunoEntity.getStatusCode().value()).isEqualTo(HttpStatus.UNAUTHORIZED.value());
    //
    //        HttpHeaders headers = new HttpHeaders();
    //        headers.setContentType(MediaType.APPLICATION_JSON);
    //        headers.set("Authorization", "Bearer "+token);
    //        HttpEntity<String> entity = new HttpEntity<String>("parameters", headers);
    //
    //
    //        responseAlunoEntity =
    //                 restTemplate.exchange("http://localhost:" + port + "/api/v1/alunos/1",
    //                         HttpMethod.GET,
    //                         entity, User.class);
    //
    //
    //        assertThat(responseAlunoEntity.getStatusCode().value()).isEqualTo(HttpStatus.OK.value());
    //        assertThat(responseAlunoEntity.getBody()).isNotNull();
    //        assertThat(responseAlunoEntity.getBody().getId()).isEqualTo(1);
    //    }
}
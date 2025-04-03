package pt.estgp.es.spring.controllers;

import lombok.AllArgsConstructor;
import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.security.authentication.AuthenticationManager;
import org.springframework.security.core.AuthenticationException;
import org.springframework.web.bind.annotation.CrossOrigin;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.RestController;
import pt.estgp.es.spring.domain.User;
import pt.estgp.es.spring.services.AuthenticationService;
import pt.estgp.es.spring.utils.JwtTokenUtil;
import pt.estgp.es.spring.utils.JwtUserDetailsService;

import java.util.HashMap;
import java.util.Map;

@RestController
@CrossOrigin
@AllArgsConstructor
public class JwtAuthenticationController {
    private final AuthenticationManager authenticationManager;
    private final JwtTokenUtil jwtTokenUtil;
    private final JwtUserDetailsService userDetailsService;
    private final AuthenticationService authenticationService;

    //    @PostMapping("/api/login")
    //    public ResponseEntity<?> createAuthenticationToken(@RequestBody JwtRequest authenticationRequest) throws Exception {
    //        authenticate(authenticationRequest.getUsername(), authenticationRequest.getPassword());
    //
    //        final UserDetails userDetails = userDetailsService.loadUserByUsername(authenticationRequest.getUsername());
    //        final String token = jwtTokenUtil.generateToken(userDetails);
    //
    //        return ResponseEntity.ok(new JwtResponse(token));
    //    }

    @PostMapping("/api/login")
    public ResponseEntity<Object> login(@RequestBody User user) {
        try {
            Map<String, Object> userDetailsMap = authenticationService.authenticate(user);
            return ResponseEntity.ok(userDetailsMap);
        } catch (AuthenticationException e) {
            Map<String, String> error = new HashMap<>();
            error.put(HttpStatus.UNAUTHORIZED.series().name(), HttpStatus.UNAUTHORIZED.getReasonPhrase());
            return new ResponseEntity<>(error, HttpStatus.UNAUTHORIZED);
        }
    }

    @PostMapping("/api/register")
    public ResponseEntity<Object> register(@RequestBody User user) {
        try {
            return authenticationService.register(user);
        } catch (AuthenticationException e) {
            Map<String, String> error = new HashMap<>();
            error.put(HttpStatus.BAD_REQUEST.series().name(), HttpStatus.BAD_REQUEST.getReasonPhrase());
            return new ResponseEntity<>(error, HttpStatus.BAD_REQUEST);
        }
    }

    //    private void authenticate(String username, String password) throws Exception {
    //        try {
    //            authenticationManager.authenticate(new UsernamePasswordAuthenticationToken(username, password));
    //        } catch (DisabledException e) {
    //            throw new Exception("USER_DISABLED", e);
    //        } catch (BadCredentialsException e) {
    //            throw new Exception("INVALID_CREDENTIALS", e);
    //        }
    //    }
}

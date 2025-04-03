package pt.estgp.es.spring.services;

import lombok.AllArgsConstructor;
import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.security.authentication.UsernamePasswordAuthenticationToken;
import org.springframework.security.core.Authentication;
import org.springframework.security.core.context.SecurityContextHolder;
import org.springframework.security.core.userdetails.UserDetails;
import org.springframework.security.crypto.bcrypt.BCryptPasswordEncoder;
import org.springframework.stereotype.Service;
import pt.estgp.es.spring.dao.RoleRepository;
import pt.estgp.es.spring.dao.UserRepository;
import pt.estgp.es.spring.domain.Role;
import pt.estgp.es.spring.domain.User;
import pt.estgp.es.spring.utils.CustomAuthenticationManager;
import pt.estgp.es.spring.utils.JwtTokenUtil;
import pt.estgp.es.spring.utils.JwtUserDetailsService;

import java.util.Collections;
import java.util.HashMap;
import java.util.Map;
import java.util.Optional;

@Service
@AllArgsConstructor
public class AuthenticationService {
    private final CustomAuthenticationManager customAuthenticationManager;
    private final JwtTokenUtil jwtTokenUtil;
    private final UserRepository userRepository;
    private final RoleRepository roleRepository;
    private final JwtUserDetailsService userDetailsService;
    //TODO: Review class
    //    public AuthenticationService(CustomAuthenticationManager customAuthenticationManager, JwtTokenUtil jwtTokenUtil, JwtUserDetailsService userDetailsService, UserRepository userRepository, RoleRepository roleRepository) {
    //        this.customAuthenticationManager = customAuthenticationManager;
    //        this.jwtTokenUtil = jwtTokenUtil;
    //        this.userDetailsService = userDetailsService;
    //        this.userRepository = userRepository;
    //        this.roleRepository = roleRepository;
    //    }

    public Map<String, Object> authenticate(User user) {
        Authentication authentication = customAuthenticationManager.authenticate(new UsernamePasswordAuthenticationToken(user.getUsername(), user.getPassword()));
        SecurityContextHolder.getContext().setAuthentication(authentication);

        // Load UserDetails from username
        UserDetails userDetails = userDetailsService.loadUserByUsername((String) authentication.getPrincipal());
        User userFromDb = userRepository.findByUsername(user.getUsername());
        final String token = jwtTokenUtil.generateToken(userDetails);

        // Create a map to hold the user details
        Map<String, Object> userDetailsMap = new HashMap<>();
        userDetailsMap.put("id", userFromDb.getId());
        userDetailsMap.put("username", userFromDb.getUsername());
        userDetailsMap.put("firstName", userFromDb.getFirstName());
        userDetailsMap.put("lastName", userFromDb.getLastName());
        userDetailsMap.put("role", userFromDb.getRole());
        userDetailsMap.put("token", token);

        return userDetailsMap;
    }

    public ResponseEntity<Object> register(User user) {
        // Check if the user already exists
        if (userRepository.findByUsername(user.getUsername()) != null) {
            // Return a response entity with a custom error message
            return new ResponseEntity<>(Collections.singletonMap("message", "message: User already exists"), HttpStatus.BAD_REQUEST);
        }

        // Hash the password
        String hashedPassword = new BCryptPasswordEncoder().encode(user.getPassword());
        user.setPassword(hashedPassword);

        // Fetch the role from the RoleRepository - Setting '1' as Default
        Optional<Role> userRoleOptional = roleRepository.findById(1);
        if (userRoleOptional.isEmpty()) {
            return new ResponseEntity<>(Collections.singletonMap("message", "Role not found"), HttpStatus.BAD_REQUEST);
        }

        // Set the role for the user
        user.setRole(userRoleOptional.get());

        // Save the new user in the database
        userRepository.save(user);

        User userFromDb = userRepository.findByUsername(user.getUsername());
        UserDetails userDetails = userDetailsService.loadUserByUsername(user.getUsername());
        final String token = jwtTokenUtil.generateToken(userDetails);

        // Create a map to hold the user details
        Map<String, Object> userDetailsMap = new HashMap<>();
        userDetailsMap.put("id", userFromDb.getId());
        userDetailsMap.put("username", userFromDb.getUsername());
        userDetailsMap.put("firstName", userFromDb.getFirstName());
        userDetailsMap.put("lastName", userFromDb.getLastName());
        userDetailsMap.put("role", userFromDb.getRole());
        userDetailsMap.put("token", token);

        // Return the saved user
        return new ResponseEntity<>(userDetailsMap, HttpStatus.CREATED);
    }
}

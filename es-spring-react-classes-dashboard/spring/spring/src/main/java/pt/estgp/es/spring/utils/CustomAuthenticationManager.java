package pt.estgp.es.spring.utils;


import lombok.AllArgsConstructor;
import org.springframework.security.authentication.AuthenticationManager;
import org.springframework.security.authentication.BadCredentialsException;
import org.springframework.security.authentication.UsernamePasswordAuthenticationToken;
import org.springframework.security.core.Authentication;
import org.springframework.security.core.AuthenticationException;
import org.springframework.security.core.GrantedAuthority;
import org.springframework.security.core.authority.SimpleGrantedAuthority;
import org.springframework.security.crypto.password.PasswordEncoder;
import org.springframework.stereotype.Service;
import pt.estgp.es.spring.dao.UserRepository;
import pt.estgp.es.spring.domain.Role;
import pt.estgp.es.spring.domain.User;

import java.util.ArrayList;
import java.util.List;

@Service
@AllArgsConstructor
public class CustomAuthenticationManager implements AuthenticationManager {
    private final PasswordEncoder passwordEncoder;
    private final UserRepository userRepository;

    @Override
    public Authentication authenticate(Authentication authentication) throws AuthenticationException {
        User user = userRepository.findByUsername(authentication.getName());
        if (user != null) {
            if (passwordEncoder.matches(authentication.getCredentials().toString(), user.getPassword())) {
                List<GrantedAuthority> grantedAuthorityList = new ArrayList<>();
                Role role = user.getRole();
                grantedAuthorityList.add(new SimpleGrantedAuthority(role.getName()));
                return new UsernamePasswordAuthenticationToken(authentication.getPrincipal(), authentication.getCredentials(), grantedAuthorityList);
            } else {
                throw new BadCredentialsException("Wrong Password");
            }
        } else {
            throw new BadCredentialsException("Wrong Username");
        }
    }
}
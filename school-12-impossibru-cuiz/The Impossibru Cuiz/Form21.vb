Public Class Form21
    Private Sub Form2_Load(sender As Object, e As EventArgs) Handles MyBase.Load
        lifes()
    End Sub
    Private Sub PictureBox1_Click(sender As Object, e As EventArgs) Handles PictureBox1.Click
        Vidas = Vidas - 1
        lifes()
        If Vidas = 0 Then
            Form1.Show()
            Me.Close()
        End If
    End Sub

    Private Sub PictureBox2_Click(sender As Object, e As EventArgs) Handles PictureBox2.Click
        Vidas = Vidas - 1
        lifes()
        If Vidas = 0 Then
            Form1.Show()
            Me.Close()
        End If
    End Sub

    Private Sub PictureBox3_Click(sender As Object, e As EventArgs) Handles PictureBox3.Click
        Vidas = Vidas - 1
        lifes()
        If Vidas = 0 Then
            Form1.Show()
            Me.Close()
        End If
    End Sub

    Private Sub PictureBox4_Click(sender As Object, e As EventArgs) Handles PictureBox4.Click
        Form22.Show()
        Me.Close()
    End Sub
    Private Sub lifes()
        If Vidas = 3 Then
            PictureBox5.Visible = True
            PictureBox6.Visible = True
            PictureBox7.Visible = True
        ElseIf Vidas = 2 Then
            PictureBox5.Visible = True
            PictureBox6.Visible = True
            PictureBox7.Visible = False
        ElseIf Vidas = 1 Then
            PictureBox5.Visible = True
            PictureBox6.Visible = False
            PictureBox7.Visible = False
        ElseIf Vidas = 0 Then
            PictureBox5.Visible = False
            PictureBox6.Visible = False
            PictureBox7.Visible = False
        End If
    End Sub
End Class
package teste.git.Testepessoa;



public class Pessoa 
{
	
	private String id;
	private String nome; 
	private String cpf;
	private DataNascimento data;
	private Endereco localizacao;
	
	public Pessoa()
	{
		data = new DataNascimento();
		localizacao = new Endereco();
	}
	
	public void setID(String id)
	{
		//this is sparta
		this.id = id;
		
	}

	public void setNome(String nome)
	{

		this.nome = nome;
		
	}
	
	
	public void setCPF(String cpf)
	{
		
		this.cpf = cpf;
		
	}

	public void setEndereco(Endereco endereco)
	{
		
		localizacao = endereco;
	}
	
	public void setEndereco(String id ,String cep ,String bairro , String estado ,String rua , 
			String complemento)
	{
		localizacao.setID(id);
		localizacao.setCEP(cep);
		localizacao.setBairro(bairro);
		localizacao.setEstado(estado);
		localizacao.setRua(rua);
		localizacao.setComplemento(complemento);	
	}
	
	public String getID()
	{
		
		return id;
		
	}

	public String getNome()
	{
	
		return nome;
		
	}
	
	
	public String getCPF()
	{
	
		return cpf;
		
	}
	
	public Endereco getEndereco()
	{
		
		return localizacao;
	}

	
	
	public String toString()
	{
		

		return "ID:" + id + " " + "Nome:" + nome + " " + "CPF:"
		+ cpf + " " + localizacao.toString();
	}

}

package teste.git.Testepessoa;

public class Endereco {

	private String id;
	private String cep;
	private String bairro;
	private String estado;
	private String rua;
	private String complemento;
	
	public Endereco()
	{
		id = null ;
		cep = null;
		bairro = null;
		estado = null ;
		estado = null;
		rua = null;
		complemento = null;
	}
	
	public void setID(String id)
	{
		//this is sparta
		this.id = id ;
		
	}
	
	public void setCEP(String cep)
	{
		
		this.cep = cep;
	}

	public void setBairro(String bairro)
	{
		
		this.bairro = bairro;
		
	}
	
	public void setEstado(String estado)
	{
	
		this.estado = estado;
	}
	
	public void setRua(String rua)
	{
		
		this.rua = rua;
	}
	
	public void setComplemento(String complemento)
	{
		
		this.complemento = complemento;
	}

	public String getID()
	{
		
		return id;
	}
	
	public String getCEP()
	{
		
		return cep;
	}

	public String getBairro()
	{
		
		return bairro;
	}
	
	public String getEstado()
	{
		
		return estado;
	}
	
	
	public String getRua()
	{
		
		return rua;
	}
	
	public String getComplemento()
	{
		
		return complemento;
	}

	public String toString()
	{
		
		return "CEP:" + cep + " " + "Bairro:" + bairro + " " + "Estado:"
		+ estado + " " + "Rua:" + rua + " " + "Complemento:" + complemento + " " + "ID:" + id;
	}
}
